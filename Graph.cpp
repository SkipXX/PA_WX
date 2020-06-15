#include "Graph.h"
#include <string>
#include <sstream>
#include <cmath>
#include <exception>
#include <algorithm>
#include <thread>

using namespace std;

//PAIR === pair<double,complex<double> >

//ease of use overloading of output operator for PAIR;
//!ONLY REAL PART
ostream& operator<<(ostream& out, const PAIR& p){
    out << p.first << ' ' << p.second.real();
return out;
}


//simply reads in data from file, first column is x second y and rest of line is discarded
istream& operator>>(istream& in, Graph& graph){
string line;
double x,y;
while(getline(in, line)){
    istringstream line_stream{line};
    line_stream >> x >> y;
    graph.push_back(x,y);
}
return in;
}

//push_back equivalent for graphs
void Graph::push_back(const double& x, const double& real, const double& imag){
data.push_back(PAIR(x,complex<double>(real,imag)));
return;
}


//returns PAIR at position ii
PAIR& Graph::operator[](int ii){
return data[ii];
}


ostream& operator<<(ostream& out, const Graph& graph){

for(const auto& ii : graph.data){
    out << ii << ' ' <<ii.second.imag() <<'\n';
}
return out;
}

//normalizes to 1, ONLY REAL PART
Graph& Graph::norm(const double norm_value){
if(this->size() == 0)return *this;

double N=0;
for(const auto& ii : data){
    N+=abs(ii.second.real());
}
N/=norm_value;
if(N==0) throw runtime_error("fkt: norm, N==0");

//INVERSE FOR FASTER CALCULATION
N=1/N;
for(auto& ii : data){
    ii.second.real(ii.second.real()*N);
}
return *this;
}

//normalizes to size
Graph& Graph::N_norm(void){
this->norm(this->size());
return *this;
}


//formats and interpolates by linear approximation
Graph& Graph::lin_format(const double _dPhi,const double _startPhi, const double _endPhi){
    int N=((_endPhi-_startPhi)/_dPhi) + 1; //+1: for X=startPhi
    int N_points=this->size();

    if(N<0) throw runtime_error("fkt: Graph::lin_format, N<0");

    Graph out_graph(N);

    double startX=data[0].first;
    double endX=data[this->size()-1].first;
    double X;

    for(int ii=0,jj=0;ii<N;++ii){
        X=_startPhi+_dPhi*ii;

        out_graph[ii].first=X;


        //assures that X is in range of original graph
//        //sets everything else to 0
//        if(X<startX) continue;
//        if(X>endX) continue;
        //sets everything to boundary
        if(X<startX){out_graph.Y(ii,(Y(0)+Y(1)+Y(2))/3);continue;}
        if(X>endX){out_graph.Y(ii,(Y(size()-3)+Y(size()-2)+Y(size()-1))/3);continue;}

        //sets everything else to start/end point value
        /*
        if(X<startX) {out_graph[ii].second.real(data[0].second.real());continue;}
        if(X>endX) {out_graph[ii].second.real(data[this->size()-1].second.real());break;}
        */
        //finds first point in original that is higher than the interpolated point
        while(jj<N_points){
            if(X<data[jj].first)break;
            ++jj;
        }

        //LINEAR APPROXIMATION
        double leftX=data[jj-1].first,rightX=data[jj].first;
        double leftY=data[jj-1].second.real(),rightY=data[jj].second.real();

        //just in case, if both are same point, should not happen
        if(rightX==leftX)out_graph[ii].second.real(rightY);


        double k = (rightY-leftY)/(rightX-leftX);
        double d = leftY - k * leftX;

        double Y = k * X + d;

        out_graph[ii].second.real(Y);

    }

    *this=out_graph;

return *this;
}


Graph& Graph::KDE_format(const double dPhi,double K, int K_type, const double startPhi, const double endPhi){
    if(K_type != 1) throw runtime_error("fkt: KDE_format; unknown Kernel type");
    if(K < 1) throw runtime_error("fkt: KDE_format; K < 1");

    //TYPES OF KERNELS
    //x: -1 < x < 1
    auto K_Epanechnikov = [](const double& x){return 0.75*(1 - x*x);};//!THIS DOES NOT ACTUALLY HAVE TO BE CALCULATED EVERY TIME
//    auto K_Gaussian = [](const double& x){static constexpr double A = 1/sqrt(2*3.14159265358);return A*log(-0.5*x*x);};
//    auto K_Triangular = [](const double& x){return (1 - abs(x));};
    //

    int N=((endPhi-startPhi)/dPhi) + 1; //+1: for X=startPhi
    int N_points=this->size();

    if(N<1) throw runtime_error("fkt: Graph::KDE_format, N<1");

    Graph out(N);

    double startX=X(0);
    double endX=X(N_points-1);
    double XX;
    double w = K*dPhi;//width = 2*a
    double w_inverse = 1/w;//for faster calculation

    //Set X values and Edge Y values
    for(int ii=0;ii<N;++ii){
        XX=startPhi+dPhi*ii;
        out.X(ii,XX);
        //sets everything else to start/end point value
        if(XX<startX){out.Y(ii,(Y(0)+Y(1)+Y(2))/3);continue;}
        if(XX>endX){out.Y(ii,(Y(size()-3)+Y(size()-2)+Y(size()-1))/3);continue;}
    }

    for(int ii=0,jj=0,kk=0;ii<N;++ii){
        XX=startPhi+dPhi*ii;

        //finds first point in original that is higher than the interpolated point
        while(jj<N_points){
            if(XX - w < X(jj))break;
            ++jj;
        }
        kk=jj; //start to search;
        //finds first point in original that is higher than the interpolated point
        while(kk<N_points){
            if(XX + w < X(kk))break;
            ++kk;
        }
        --kk;

        //KDE APPROXIMATION
        double YY=0;
        for(int nn=jj;nn<=kk;++nn){
            YY+= Y(nn)*K_Epanechnikov((X(nn)-out.X(ii))*w_inverse);
        }



        out.Y(ii,YY);
    }

    *this=out;

return *this;
}



Graph& Graph::format(const double dP){
    if(this->size() == 0) return *this;
this->lin_format(dP,this->data[0].first,data[this->size()-1].first);
return *this;
}

Graph& Graph::format_ALL(const double dP){
    if(this->size() == 0) return *this;
this->lin_format(dP,startPhi,endPhi);
return *this;
}


//implements a naive discrete fourier transform
Graph& Graph::DFT(bool inverse){
    Graph temp(*this);
    double pi2 = 2.0 * 3.14159265358;
    double angleTerm,cosineA,sineA;
    int N = this->size();
    double invs = 1.0 / N;
    double d_tmp;

for(int y =0; y<N;++y){
    data[y].second=0;

    for(int x = 0; x<N; ++x){
        angleTerm = pi2 * y * x *invs;
        if(inverse)angleTerm=-angleTerm;
        cosineA = cos(angleTerm);
        sineA = sin(angleTerm);

        d_tmp = temp[x].second.real() * cosineA - temp[x].second.imag() * sineA;
        data[y].second.real(data[y].second.real()+d_tmp);

        d_tmp = temp[x].second.real() * sineA - temp[x].second.imag() * cosineA;
        data[y].second.imag(data[y].second.imag()+d_tmp);

    }
    data[y].second *= invs;
}

    return *this;
}


//implements a naive discrete fourier transform
Graph& Graph::DFT_MT(bool inverse){
    int N=this->size();
    Graph temp(*this);

    auto dft_for = [](Graph* t,Graph temp,bool inverse,int A,int B){
        double pi2 = 2.0 * 3.14159265358;
        double angleTerm,cosineA,sineA;
        int N = t->size();
        double invs = 1.0 / N;
        double d_tmp;

        for(int y =A; y<B;++y){
            t->Y(y,0);
            t->Z(y,0);

            for(int x = 0; x<N; ++x){
                angleTerm = pi2 * y * x *invs;
                if(inverse)angleTerm=-angleTerm;
                cosineA = cos(angleTerm);
                sineA = sin(angleTerm);

                d_tmp = temp[x].second.real() * cosineA - temp[x].second.imag() * sineA;
                t->Y(y,t->Y(y)+d_tmp);

                d_tmp = temp[x].second.real() * sineA - temp[x].second.imag() * cosineA;
                t->Z(y,t->Z(y)+d_tmp);

            }
            t->Y(y,t->Y(y)*invs);
            t->Z(y,t->Z(y)*invs);
        }

        return *t;



    };


    thread t1(dft_for,this,temp,inverse,0,N/3);
    thread t2(dft_for,this,temp,inverse,N/3,N*2/3);
    thread t3(dft_for,this,temp,inverse,N*2/3,N);

    t1.join();
    t2.join();
    t3.join();

    return *this;
}




//sets Graph zero from index startP to endP
Graph& Graph::set_zero(int startP, int endP){
int N=this->size();
if(startP < 0 || endP >= N) throw out_of_range("fkt: Graph::set_zero");

for(int ii=startP;ii<=endP;++ii){
    data[ii].second.real(0);
    data[ii].second.imag(0);
}

return *this;
}

//sets negativ Y values to 0
Graph& Graph::neg_zero(){
for(int ii=0;ii<this->size();++ii){
    if(Y(ii)<0)Y(ii,0);
}
return *this;
}

//multiplies two graphes, does NOT normalize, MUST BE SAME SIZE
Graph operator*(const Graph& graph1,const Graph& graph2){
Graph temp(graph1);

if(graph1.size() != graph2.size()) throw runtime_error("fkt: Graph.operator*, not same size");

for(int ii=0;ii<temp.size();++ii){
    temp.data[ii].second *= graph2.data[ii].second;
}

return temp;
}

//subtracts value from every Y value;
Graph operator-(const Graph& graph, const double& value){
Graph out_graph(graph);
for(int ii=0;ii<out_graph.size();++ii){
    out_graph.Y(ii,out_graph.Y(ii)-value);
}
return out_graph;
}

//PEAK EVALUATION FUNCTIONS
///////////////////////////
//BEST VALUES: k=20,h=0.6;
double S1(const Graph& graph,int ii,int k=20){
    double max_left,max_right;
    int N = graph.size();
    if(ii-k < 0 || ii+k >= N) return false; //exclude points at start and end

    auto dY = [graph,ii](int kk){return graph.Y(ii)-graph.Y(kk);};


    max_left = dY(ii-k);
    for(int jj=ii-k;jj<ii;++jj){
        if(dY(jj)>max_left)max_left=dY(jj);
    }

    max_right = dY(ii+1);
    for(int jj=ii+1;jj<ii+k+1;++jj){
        if(dY(jj)>max_right)max_right=dY(jj);
    }

return (max_left+max_right)/2;
}
//BEST VALUES: 10,0.3
double S2(const Graph& graph,int ii,int k=10){
    double left=0,right=0;
    int N = graph.size();
    if(ii-k < 0 || ii+k >= N) return 0; //exclude points at start and end

    auto dY = [graph,ii](int kk){return graph.Y(ii)-graph.Y(kk);};
    for(int jj=ii-k;jj<ii;++jj){
        left+=dY(jj);
    }
    for(int jj=ii+1;jj<ii+k+1;++jj){
        right+=dY(jj);
    }

return (left+right)/2.0/k;
}

double S3(const Graph& graph,int ii,int k=10){
    double left=0,right=0;
    int N = graph.size();

    if(ii-k < 0 || ii+k >= N) return 0; //exclude points at start and end

    for(int jj=ii-k;jj<ii;++jj){
        left+=graph.Y(jj);
    }
    for(int jj=ii+1;jj<ii+k+1;++jj){
        right+=graph.Y(jj);
    }

return graph.Y(ii)-0.5*(left+right)/k;
}

//! CREATE INDEPENDENT RHO FKT FOR KDE

double S4(Graph& graph,int ii,int k=25){
    double Hmit=0,Hohne=0;
    //static constexpr double A=1.0/sqrt(2*3.21415926);
    double YY=graph.Y(ii);

    //Edge Peaks are ignored
    if(ii-2*k<0 || ii+2*k >= graph.size())return 0;

    double w_inverse = 2.0/(graph.X(ii+k)-graph.X(ii-k));

    auto p = [k,w_inverse](const Graph& graph,int jj){
        auto K_Epanechnikov = [](const double& x){return 0.75*(1 - x*x);};

        double PP=0;
        for(int nn=jj-k;nn<=jj+k;++nn){
            PP+= graph.Y(nn)*K_Epanechnikov((graph.X(nn)-graph.X(jj))*w_inverse);
        }
        return PP;
    };

    double PP;
    for(int nn=ii-k;nn<=ii+k;++nn){
        PP=p(graph,nn);
        Hmit += -PP*log(PP);
    }
    graph.Y(ii,0);
    for(int nn=ii-k;nn<=ii+k;++nn){
        PP=p(graph,nn);
        Hohne += -PP*log(PP);
    }
    graph.Y(ii,YY);

return Hohne-Hmit;
}


bool S_MY_1(const Graph& graph,int ii,int k=200){
//    if(ii-k < 0 || ii+k >= graph.size()) return false; //OUT OF RANGE CHECKS -> k EDGE POINTS IGNORED

    double MIN,AVG;
    bool peak1=false,peak2=false;
    for(int kk=5;kk<=k;++kk){
        if(ii-kk < 0 || ii+kk >= graph.size()) continue;

        //calculate MIN AND AVG
        MIN=graph.Y(ii-kk);
        for(int jj=ii-kk;jj<ii+kk+1;++jj){
            if(graph.Y(jj)<MIN)MIN=graph.Y(jj);
        }
        AVG=0;
        for(int jj=ii-kk;jj<ii+kk+1;++jj){
            AVG+=graph.Y(jj)-MIN;
        }
        AVG/=2.0*kk+1.0;
        //////////////////////

//        //IF POINT IS EVER MUCH HIGHER THAN AVERAGE -> PEAK
        if((graph.Y(ii-1) + graph.Y(ii)*3 + graph.Y(ii+1))/5 - MIN > 3*AVG) peak1=true;
        if(kk>k/2  && (graph.Y(ii-1) + graph.Y(ii)*3 + graph.Y(ii+1))/5 - MIN > 1.5*AVG) peak2=true;


    }
return peak1&&peak2;
}

//default type = 4
vector<int> Graph::find_peaks(int k,double h,int type){
    vector<int> peaks;

    for(int ii=1;ii<size()-1;++ii){
        if(Y(ii)<Y(ii+1))continue;
        if(Y(ii)<Y(ii-1))continue;

//        if(Y(ii)<Y(ii+2))continue;
//        if(Y(ii)<Y(ii-2))continue;

        //!CODE NOT REALLY OPTIMAL, STD::UNORDERED_MAP, HMM

        switch(type){
        case 1:
            if(S1(*this,ii,k) > h)peaks.push_back(ii);
            break;
        case 2:
            if(S2(*this,ii,k) > h)peaks.push_back(ii);
            break;
        case 3:
            if(S3(*this,ii,k) > h)peaks.push_back(ii);
            break;
        case 4:
            if(S4(*this,ii,k) > h)peaks.push_back(ii);
            break;
        default:
            throw std::runtime_error("fkt: Graph::find_peaks, unrecognized type");
        }
    }
    std::sort(peaks.begin(),peaks.end());
return peaks;
}

double Graph::min(int a, int b)const{
    if(a==-1)a=0;
    if(b==-1)b=size()-1;
    double MIN=Y(a);

    for(int ii=a;ii<=b;++ii){
        if(MIN>Y(ii)) MIN=Y(ii);
    }
return MIN;
}

double Graph::max(int a, int b) const{
    if(a==-1)a=0;
    if(b==-1)b=size()-1;
    double MAX=Y(a);

    for(int ii=a;ii<=b;++ii){
        if(MAX<Y(ii)) MAX=Y(ii);
    }
return MAX;
}

double Graph::avg(int a,int b) const{
    double AVG=0;
    if(a==-1)a=0;
    if(b==-1)b=size()-1;

    for(int ii=a;ii<=b;++ii) AVG += Y(ii);

    AVG /= b-a+1;

return AVG;
}


Graph operator*(const Graph& graph,const double& value){
    Graph out(graph);
    for(int ii=0;ii<out.size();++ii){
        out.Y(ii,out.Y(ii)*value);
    }
return out;
}


Graph& Graph::remove_background(int k,int cut_high, int cut_low){
    int N = size();
    if(N == 0) return *this;
    vector<double> area;
    Graph out(*this);
    double AVG;

    if(cut_low+cut_high+2 >= N) throw runtime_error("fkt: Graph::remove_background, cut area is bigger than size");

    for(int ii=0;ii<N;++ii){
        if(ii-k < 0 || ii+k >= N) continue; //exclude points at start and end
        AVG=0;

        //reserve memory for faster push_back
        area.reserve(2*k+1);

        //get all points into area
        for(int jj=ii-k;jj<ii+k+1;++jj){
            area.push_back(Y(jj));
        }
        sort(area.begin(),area.end());

        //REMOVES HIGHEST AND LOWEST POINTS TO REMOVE EXTREME VALUES, LIKE PEAKS
        area.erase(area.begin(),area.begin()+cut_low);
        area.erase(area.end()-cut_high,area.end());

        //calculate AVERAGE
        for(auto& jj : area){
            AVG+=jj;
        }
        AVG/=area.size();

        //SUBTRACT AVERAGE OF AREA -> LINEAR APPROXIMATION OF BACKGROUND
        out.Y(ii,Y(ii)-AVG);
        if(ii-k == 0){//!THIS MAY NOT BE SMART
           for(int kk=0;kk<ii;++kk)out.Y(kk,Y(ii)-AVG);//AVG OF EDGE CASES IS APPROXIMATLY CONST

        }
        if(ii+k == N-1){for(int kk=ii+1;kk<N;++kk)out.Y(kk,Y(ii)-AVG);}

        area.clear();
    }
    *this=out;
return *this;
}


Graph& Graph::remove_noise(double dPhi,int K,int K_type){
//    Graph temp(*this);
//    for(int ii=2;ii<size()-2;++ii){
////        Y(ii,(temp.Y(ii-3)+temp.Y(ii-2)+2*temp.Y(ii-1)+4*temp.Y(ii)+2*temp.Y(ii+1)+temp.Y(ii+2)+temp.Y(ii+3))/11);
//        Y(ii,(temp.Y(ii-2)+2*temp.Y(ii-1)+4*temp.Y(ii)+2*temp.Y(ii+1)+temp.Y(ii+2))/8);
//    }
    if(this->size() < 1) return *this;
    KDE_format(dPhi,K,K_type,X(0),X(this->size()-1));
return *this;
}

Graph& Graph::MAX_norm(double value){
    if(this->size() < 1 ) return *this;

    double MAX = this->max();
    if(MAX==0.0)return *this;

    double faktor=value/MAX;

    for(int ii=0;ii<size();++ii){
        Y(ii,Y(ii)*faktor);//multiplies each by faktor
    }
return *this;
}


