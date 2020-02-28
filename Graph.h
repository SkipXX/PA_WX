#ifndef _MY_GRAPH_
#define _MY_GRAPH_



#include <vector>
#include <iostream>
#include <utility>
#include <complex>

using namespace std;

//ease of use definition
typedef pair<double,complex<double> > PAIR;

ostream& operator<<(ostream& out, const PAIR&);


//Main Class for handling of Graph Data
class Graph{
    static constexpr double dPhi=0.01,startPhi=0.0,endPhi=120.0;

    vector<PAIR> data;

public:

    //!HMMM, MIGHT NOT BE BEST TO DO THIS HERE, and not public but whatever
    bool isFourier=false;

    Graph(){}//default constructor
    Graph(int ii) : data(ii){}//preconstructs with ii elements
    //Graph(ifstream& in);//constructs from file, first column should be x and second y
    ~Graph(){}

    PAIR& operator[](int ii); //returns PAIR at position ii

    //complex<double> operator()(double x); //tries to find closes approximation for y(x)
    void push_back(const double& x, const double& y, const double& imag=0); //push_back equivalent for graphs
    void clear(){data.clear();isFourier=false;}//resets graph

    //funktions to access X and Y
    inline const double X(int i) const{return data[i].first;}
    inline void X(int i,double value){data[i].first=value;}
    const double X(double i)const = delete;//bug catching
    inline const double Y(int i)const{return data[i].second.real();}
    inline void Y(int i,double value){data[i].second.real(value);}
    const double Y(double i)const = delete;//bug catching
    inline const double Z(int i)const{return data[i].second.imag();}
    inline void Z(int i,double value){data[i].second.imag(value);}
    const double Z(double i)const = delete;//bug catching



    friend istream& operator>>(istream& in, Graph& graph); //creates Graph from a formated text file, first column should be x and second y
    friend ostream& operator<<(ostream& out, const Graph& graph); //outputs Graph

    friend Graph Interpolate(const Graph& graph, const double dPhi=dPhi, const double startPhi=startPhi, const double endPhi=endPhi);
    friend Graph Interpolate_ALL(const Graph& graph, const double dPhi=dPhi, const double startPhi=startPhi, const double endPhi=endPhi);

    //!const
    friend Graph operator*(const Graph& graph1,const Graph& graph2);//multiplies two graphes, does NOT normalize, MUST BE SAME SIZE
    friend Graph operator*(const Graph& graph,const double& value);//multiplies all Y by value
    friend Graph operator-(const Graph& graph, const double& value);//subtracts all Y by value

    //interpolates and formats data into data from startPhi to endPhi in steps of dPhi
    Graph& lin_format(const double dPhi, const double start, const double end);
    Graph& KDE_format(const double dPhi,double K, int K_type, const double start, const double end);//Kernel Distribution Estimation;
    //K: half of kernel width; K_type: type of Kernel used, 1 = Epanechnikov(parabolic)

    Graph& format(const double dPhi=dPhi); //interpolates and formats into steps of dPhi, keeps start and end
    Graph& format_ALL(const double dPhi=dPhi); //interpolates and formats data into data from startPhi to endPhi in steps of dPhi



    Graph& norm(const double norm_value=1); //normalizes graph, USE ONLY WHEN ONLY REAL NONZERO
    Graph& N_norm(void); //normalizes graph to N, where N is the number of Points
    Graph& MAX_norm(double value);//normalizs graph so that the highest point is value

    /*!DOES NOT WORK*/Graph& FFT(bool inverse=false); //applies fast fourier transform
    Graph& DFT(bool inverse=false);//applies discrete fourier transform
    Graph& DFT_MT(bool inverse=false);//Multithreaded DFT

    Graph& set_zero(int startPoint, int endPoint);//sets Graph to 0 in this range
    Graph& neg_zero();//sets negativ values to 0
    Graph& remove_background(int k, int cut_high=0, int cut_low=0);//tries to remove background by approximating local background as linear, 2*k is size of local area
    Graph& remove_noise(double dPhi,int K,int K_type=1);//tries to remove noise by averaging points


    vector<int> find_peaks(int k, double h, int type=4);//fings peaks and returns their positions as an int vector, sorted by height
    double min(int a=-1,int b=-1) const;//value of min Y; default: -1 -> start to end
    double max(int a=-1,int b=-1) const;//value of max Y; default: -1 -> start to end
    double avg(int a=-1,int b=-1) const;//average value from index a to b; default: -1 -> start to end

    int size(void) const {return data.size();}


};

#endif // _MY_GRAPH_
