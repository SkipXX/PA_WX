/***************************************************************
 * Name:      PA_WXMain.h
 * Purpose:   Defines Application Frame
 * Author:     ()
 * Created:   2020-02-12
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef PA_WXMAIN_H
#define PA_WXMAIN_H



//(*Headers(PA_WXFrame)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/statusbr.h>
#include <wx/textctrl.h>
#include <wx/textdlg.h>
//*)

///MY INCLUDES ETC
#include "gnuplot-iostream.h"
#include <fstream>
#include "Graph.h"
///



class PA_WXFrame: public wxFrame
{
    public:

        PA_WXFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~PA_WXFrame();

        /// MY VARIABLES
        Gnuplot gp;
        std::ofstream out;
        Graph graph;
        Graph last_graph;
        std::vector<std::pair<double,double>> peaks;
        std::vector<std::pair<double,double>> manual_peaks;
        std::string location;


    private:

        //(*Handlers(PA_WXFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void Ongnuplot_plotClick(wxCommandEvent& event);
        void On_plot_Click(wxCommandEvent& event);
        void On_Load_File_Click(wxCommandEvent& event);
        void On_N_Norm_Click(wxCommandEvent& event);
        void On_Back_Button_Click(wxCommandEvent& event);
        void On_format_all_Click(wxCommandEvent& event);
        void On_remove_noise_Click(wxCommandEvent& event);
        void Onremove_backgroundClick(wxCommandEvent& event);
        void On_DFT_Click(wxCommandEvent& event);
        void On_neg_zero_Click(wxCommandEvent& event);
        void On_DO_STUFF_Click(wxCommandEvent& event);
        void On_Help_gnuplot_path_Selected(wxCommandEvent& event);
        void On_PEAKS_Click(wxCommandEvent& event);
        void On_Database_RELOAD_Selected(wxCommandEvent& event);
        void On_Database_OPEN_Selected(wxCommandEvent& event);
        void On_set_zero_Click(wxCommandEvent& event);
        void On_PEAK_multiplication_Click(wxCommandEvent& event);
        void On_Save_Graph_Click(wxCommandEvent& event);
        void On_standard_format_Click(wxCommandEvent& event);
        void On_show_again_Click(wxCommandEvent& event);
        void On_add_peak_Click(wxCommandEvent& event);
        void On_clear_manual_peaks_Click(wxCommandEvent& event);
        void On_HowToUse_Selected(wxCommandEvent& event);
        void On_WhatIsKDE_Selected(wxCommandEvent& event);
        void On_Sourcecode_Selected(wxCommandEvent& event);
        //*)

        //(*Identifiers(PA_WXFrame)
        static const long ID_STATICBOX6;
        static const long ID_CHECKBOX3;
        static const long ID_STATICBOX5;
        static const long ID_STATICBOX3;
        static const long ID_STATICBOX4;
        static const long ID_STATICBOX2;
        static const long ID_dPhi;
        static const long ID_STATICBOX1;
        static const long ID_BUTTON1;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
        static const long ID_TEXTCTRL3;
        static const long ID_CHECKBOX1;
        static const long ID_BUTTON4;
        static const long ID_BUTTON5;
        static const long ID_CHECKBOX2;
        static const long ID_BUTTON6;
        static const long ID_BUTTON7;
        static const long ID_TEXTCTRL2;
        static const long ID_TEXTCTRL4;
        static const long ID_BUTTON8;
        static const long ID_TEXTCTRL5;
        static const long ID_TEXTCTRL6;
        static const long ID_TEXTCTRL7;
        static const long ID_BUTTON9;
        static const long ID_BUTTON10;
        static const long ID_TEXTCTRL8;
        static const long ID_TEXTCTRL9;
        static const long ID_CHOICE1;
        static const long ID_BUTTON11;
        static const long ID_BUTTON12;
        static const long ID_PEAKS_epsilon;
        static const long ID_set_zero;
        static const long ID_set_zero_start;
        static const long ID_set_zero_end;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_PEAK_multiplication;
        static const long ID_Save_Graph;
        static const long ID_STATICTEXT3;
        static const long ID_standard_format;
        static const long ID_STATICTEXT4;
        static const long ID_show_again;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_STATICTEXT7;
        static const long ID_STATICTEXT8;
        static const long ID_STATICTEXT9;
        static const long ID_STATICBOX7;
        static const long ID_add_peak;
        static const long ID_clear_manual_peaks;
        static const long ID_X_man_peak;
        static const long ID_STATICTEXT10;
        static const long ID_Y_man_peak;
        static const long ID_STATICTEXT11;
        static const long ID_MENUITEM3;
        static const long ID_MENUITEM2;
        static const long ID_MENUITEM1;
        static const long ID_MENUITEM4;
        static const long ID_MENUITEM5;
        static const long ID_MENUITEM6;
        static const long ID_STATUSBAR1;
        static const long ID_TEXTENTRYDIALOG1;
        //*)

        //(*Declarations(PA_WXFrame)
        wxButton* Back_Button;
        wxButton* Button1;
        wxButton* DFT;
        wxButton* DO_STUFF;
        wxButton* Load_File;
        wxButton* PEAKS;
        wxButton* PEAK_multiplication;
        wxButton* Save_Graph;
        wxButton* add_peak;
        wxButton* clear_manual_peaks;
        wxButton* format_al;
        wxButton* gnuplot_plot;
        wxButton* neg_zero;
        wxButton* plot;
        wxButton* remove_background;
        wxButton* remove_noise;
        wxButton* set_zero;
        wxButton* show_again;
        wxButton* standard_format;
        wxCheckBox* check_auto_N_Norm;
        wxCheckBox* check_auto_plot;
        wxCheckBox* plot_peaks;
        wxChoice* plot_peaks_type;
        wxMenu* Menu3;
        wxMenuItem* Database_OPEN;
        wxMenuItem* Database_RELOAD;
        wxMenuItem* Help_gnuplot_path;
        wxMenuItem* HowToUse;
        wxMenuItem* Sourcecode;
        wxMenuItem* WhatIsKDE;
        wxStaticBox* StaticBox1;
        wxStaticBox* StaticBox2;
        wxStaticBox* StaticBox3;
        wxStaticBox* StaticBox4;
        wxStaticBox* StaticBox5;
        wxStaticBox* StaticBox6;
        wxStaticBox* StaticBox7;
        wxStaticText* StaticText10;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxStaticText* StaticText5;
        wxStaticText* StaticText6;
        wxStaticText* StaticText7;
        wxStaticText* StaticText8;
        wxStaticText* StaticText9;
        wxStaticText* dPhi;
        wxStaticText* epsilon;
        wxStatusBar* StatusBar1;
        wxTextCtrl* Load_File_Text;
        wxTextCtrl* PEAKS_epsilon;
        wxTextCtrl* X_man_peak;
        wxTextCtrl* Y_man_peak;
        wxTextCtrl* dPhi_textbox;
        wxTextCtrl* gnuplot_plot_text;
        wxTextCtrl* plot_peaks_H;
        wxTextCtrl* plot_peaks_K;
        wxTextCtrl* remove_background_K;
        wxTextCtrl* remove_background_cut_high;
        wxTextCtrl* remove_background_cut_low;
        wxTextCtrl* remove_noise_K;
        wxTextCtrl* set_zero_end;
        wxTextCtrl* set_zero_start;
        wxTextEntryDialog* Database_RELOAD_INPUT;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // PA_WXMAIN_H
