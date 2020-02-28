/***************************************************************
 * Name:      PA_WXMain.cpp
 * Purpose:   Code for Application Frame
 * Author:     ()
 * Created:   2020-02-12
 * Copyright:  ()
 * License:
 **************************************************************/
 #define BOOST_FILESYSTEM_NO_DEPRECATED

#include "PA_WXMain.h"
#include <wx/msgdlg.h>

///MY INCLUDES
#include <boost/dll/runtime_symbol_info.hpp>
#include <sstream>
#include <tuple>
#include <utility>

#include <wx/filedlg.h>
///

//(*InternalHeaders(PA_WXFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(PA_WXFrame)
const long PA_WXFrame::ID_STATICBOX6 = wxNewId();
const long PA_WXFrame::ID_CHECKBOX3 = wxNewId();
const long PA_WXFrame::ID_STATICBOX5 = wxNewId();
const long PA_WXFrame::ID_STATICBOX3 = wxNewId();
const long PA_WXFrame::ID_STATICBOX4 = wxNewId();
const long PA_WXFrame::ID_STATICBOX2 = wxNewId();
const long PA_WXFrame::ID_dPhi = wxNewId();
const long PA_WXFrame::ID_STATICBOX1 = wxNewId();
const long PA_WXFrame::ID_BUTTON1 = wxNewId();
const long PA_WXFrame::ID_TEXTCTRL1 = wxNewId();
const long PA_WXFrame::ID_BUTTON2 = wxNewId();
const long PA_WXFrame::ID_BUTTON3 = wxNewId();
const long PA_WXFrame::ID_TEXTCTRL3 = wxNewId();
const long PA_WXFrame::ID_CHECKBOX1 = wxNewId();
const long PA_WXFrame::ID_BUTTON4 = wxNewId();
const long PA_WXFrame::ID_BUTTON5 = wxNewId();
const long PA_WXFrame::ID_CHECKBOX2 = wxNewId();
const long PA_WXFrame::ID_BUTTON6 = wxNewId();
const long PA_WXFrame::ID_BUTTON7 = wxNewId();
const long PA_WXFrame::ID_TEXTCTRL2 = wxNewId();
const long PA_WXFrame::ID_TEXTCTRL4 = wxNewId();
const long PA_WXFrame::ID_BUTTON8 = wxNewId();
const long PA_WXFrame::ID_TEXTCTRL5 = wxNewId();
const long PA_WXFrame::ID_TEXTCTRL6 = wxNewId();
const long PA_WXFrame::ID_TEXTCTRL7 = wxNewId();
const long PA_WXFrame::ID_BUTTON9 = wxNewId();
const long PA_WXFrame::ID_BUTTON10 = wxNewId();
const long PA_WXFrame::ID_TEXTCTRL8 = wxNewId();
const long PA_WXFrame::ID_TEXTCTRL9 = wxNewId();
const long PA_WXFrame::ID_CHOICE1 = wxNewId();
const long PA_WXFrame::ID_BUTTON11 = wxNewId();
const long PA_WXFrame::ID_BUTTON12 = wxNewId();
const long PA_WXFrame::ID_PEAKS_epsilon = wxNewId();
const long PA_WXFrame::ID_set_zero = wxNewId();
const long PA_WXFrame::ID_set_zero_start = wxNewId();
const long PA_WXFrame::ID_set_zero_end = wxNewId();
const long PA_WXFrame::ID_STATICTEXT1 = wxNewId();
const long PA_WXFrame::ID_STATICTEXT2 = wxNewId();
const long PA_WXFrame::ID_PEAK_multiplication = wxNewId();
const long PA_WXFrame::ID_Save_Graph = wxNewId();
const long PA_WXFrame::ID_STATICTEXT3 = wxNewId();
const long PA_WXFrame::ID_standard_format = wxNewId();
const long PA_WXFrame::ID_STATICTEXT4 = wxNewId();
const long PA_WXFrame::ID_show_again = wxNewId();
const long PA_WXFrame::ID_STATICTEXT5 = wxNewId();
const long PA_WXFrame::ID_STATICTEXT6 = wxNewId();
const long PA_WXFrame::ID_STATICTEXT7 = wxNewId();
const long PA_WXFrame::ID_STATICTEXT8 = wxNewId();
const long PA_WXFrame::ID_STATICTEXT9 = wxNewId();
const long PA_WXFrame::ID_STATICBOX7 = wxNewId();
const long PA_WXFrame::ID_add_peak = wxNewId();
const long PA_WXFrame::ID_clear_manual_peaks = wxNewId();
const long PA_WXFrame::ID_X_man_peak = wxNewId();
const long PA_WXFrame::ID_STATICTEXT10 = wxNewId();
const long PA_WXFrame::ID_Y_man_peak = wxNewId();
const long PA_WXFrame::ID_STATICTEXT11 = wxNewId();
const long PA_WXFrame::ID_MENUITEM3 = wxNewId();
const long PA_WXFrame::ID_MENUITEM2 = wxNewId();
const long PA_WXFrame::ID_MENUITEM1 = wxNewId();
const long PA_WXFrame::ID_MENUITEM4 = wxNewId();
const long PA_WXFrame::ID_MENUITEM5 = wxNewId();
const long PA_WXFrame::ID_MENUITEM6 = wxNewId();
const long PA_WXFrame::ID_STATUSBAR1 = wxNewId();
const long PA_WXFrame::ID_TEXTENTRYDIALOG1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(PA_WXFrame,wxFrame)
    //(*EventTable(PA_WXFrame)
    //*)
END_EVENT_TABLE()

PA_WXFrame::PA_WXFrame(wxWindow* parent,wxWindowID id) :
    gp("gnuplot"),//"\"C:\\Program Files\\gnuplot\\bin\\gnuplot.exe\"" ... REQUIRES PATH VARIABLE!!
    out("out.xy")
{


    //(*Initialize(PA_WXFrame)
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;

    Create(parent, wxID_ANY, _("This is an application."), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(400,500));
    StaticBox6 = new wxStaticBox(this, ID_STATICBOX6, _("Peak Calculations"), wxPoint(216,136), wxSize(176,144), 0, _T("ID_STATICBOX6"));
    plot_peaks = new wxCheckBox(this, ID_CHECKBOX3, _("Plot Peaks"), wxPoint(224,192), wxSize(88,40), 0, wxDefaultValidator, _T("ID_CHECKBOX3"));
    plot_peaks->SetValue(false);
    plot_peaks->SetToolTip(_("enables the finding of peaks when plotting"));
    StaticBox5 = new wxStaticBox(this, ID_STATICBOX5, wxEmptyString, wxPoint(8,264), wxSize(104,112), 0, _T("ID_STATICBOX5"));
    StaticBox3 = new wxStaticBox(this, ID_STATICBOX3, _("Remove Background"), wxPoint(8,152), wxSize(192,112), 0, _T("ID_STATICBOX3"));
    StaticBox3->SetToolTip(_("tries to remove linear(in the intervall) background"));
    StaticBox4 = new wxStaticBox(this, ID_STATICBOX4, _("Cut Points"), wxPoint(16,200), wxSize(176,56), 0, _T("ID_STATICBOX4"));
    StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, wxEmptyString, wxPoint(8,104), wxSize(192,48), 0, _T("ID_STATICBOX2"));
    dPhi = new wxStaticText(this, ID_dPhi, _("dPhi:"), wxPoint(16,80), wxSize(40,24), 0, _T("ID_dPhi"));
    dPhi->SetToolTip(_("distance between points on X axes"));
    StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, wxEmptyString, wxPoint(272,360), wxSize(120,80), 0, _T("ID_STATICBOX1"));
    gnuplot_plot = new wxButton(this, ID_BUTTON1, _("gnuplot <<"), wxPoint(8,8), wxSize(88,24), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    gnuplot_plot->SetToolTip(_("direct gnuplot input"));
    gnuplot_plot_text = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(104,8), wxSize(288,24), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    gnuplot_plot_text->SetToolTip(_("direct gnuplot input"));
    plot = new wxButton(this, ID_BUTTON2, _("Plot"), wxPoint(336,376), wxSize(48,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    plot->SetToolTip(_("plot graph"));
    Load_File = new wxButton(this, ID_BUTTON3, _("Load Data"), wxPoint(104,40), wxSize(88,24), 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Load_File->SetToolTip(_("keep textbox empty for file dialog"));
    Load_File_Text = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxPoint(200,40), wxSize(192,24), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    Load_File_Text->SetToolTip(_("keep textbox empty for file dialog"));
    check_auto_plot = new wxCheckBox(this, ID_CHECKBOX1, _("auto"), wxPoint(280,376), wxSize(56,21), 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    check_auto_plot->SetValue(true);
    check_auto_plot->SetToolTip(_("Plot graph after each change\?"));
    Button1 = new wxButton(this, ID_BUTTON4, _("Norm"), wxPoint(336,408), wxSize(48,24), 0, wxDefaultValidator, _T("ID_BUTTON4"));
    Button1->SetToolTip(_("Norm graph to max=100"));
    Back_Button = new wxButton(this, ID_BUTTON5, _("Back"), wxPoint(120,336), wxSize(80,40), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    Back_Button->SetToolTip(_("revert last change"));
    check_auto_N_Norm = new wxCheckBox(this, ID_CHECKBOX2, _("auto"), wxPoint(280,408), wxSize(56,24), 0, wxDefaultValidator, _T("ID_CHECKBOX2"));
    check_auto_N_Norm->SetValue(true);
    check_auto_N_Norm->SetToolTip(_("Norm graph after each change\?"));
    format_al = new wxButton(this, ID_BUTTON6, _("0-120 Format"), wxPoint(104,80), wxSize(96,24), 0, wxDefaultValidator, _T("ID_BUTTON6"));
    format_al->SetToolTip(_("formats data to range 0 to 120"));
    remove_noise = new wxButton(this, ID_BUTTON7, _("Remove Noise"), wxPoint(16,120), wxSize(104,24), 0, wxDefaultValidator, _T("ID_BUTTON7"));
    remove_noise->SetToolTip(_("applies a kernel density estimation with a parabolic kernal"));
    dPhi_textbox = new wxTextCtrl(this, ID_TEXTCTRL2, _("0.01"), wxPoint(56,80), wxSize(40,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    dPhi_textbox->SetToolTip(_("distance between points on X axes"));
    remove_noise_K = new wxTextCtrl(this, ID_TEXTCTRL4, _("5"), wxPoint(160,120), wxSize(32,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    remove_noise_K->SetToolTip(_("number of points to left/right in the kernel density estimation"));
    remove_background = new wxButton(this, ID_BUTTON8, _("start"), wxPoint(112,176), wxSize(80,24), 0, wxDefaultValidator, _T("ID_BUTTON8"));
    remove_background->SetToolTip(_("tries to remove linear(in the intervall) background"));
    remove_background_K = new wxTextCtrl(this, ID_TEXTCTRL5, _("200"), wxPoint(64,176), wxSize(40,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    remove_background_K->SetToolTip(_("number of points to left/right in the intervall"));
    remove_background_cut_high = new wxTextCtrl(this, ID_TEXTCTRL6, _("200"), wxPoint(64,224), wxSize(40,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
    remove_background_cut_high->SetToolTip(_("cuts X number of highest points to remove peaks"));
    remove_background_cut_low = new wxTextCtrl(this, ID_TEXTCTRL7, _("150"), wxPoint(144,224), wxSize(40,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL7"));
    remove_background_cut_low->SetToolTip(_("removes the X lowest points to balance out the high point removal"));
    DFT = new wxButton(this, ID_BUTTON9, _("DFT"), wxPoint(120,304), wxSize(80,24), 0, wxDefaultValidator, _T("ID_BUTTON9"));
    DFT->SetToolTip(_("fourier transform"));
    neg_zero = new wxButton(this, ID_BUTTON10, _("Neg to 0"), wxPoint(120,272), wxSize(80,24), 0, wxDefaultValidator, _T("ID_BUTTON10"));
    neg_zero->SetToolTip(_("sets all negativ values to 0"));
    plot_peaks_K = new wxTextCtrl(this, ID_TEXTCTRL8, _("50"), wxPoint(344,192), wxSize(40,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL8"));
    plot_peaks_K->SetToolTip(_("number of points to left/right in the intervall"));
    plot_peaks_H = new wxTextCtrl(this, ID_TEXTCTRL9, _("400"), wxPoint(344,216), wxSize(40,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL9"));
    plot_peaks_H->SetToolTip(_("threshhold value to determine peak"));
    plot_peaks_type = new wxChoice(this, ID_CHOICE1, wxPoint(232,160), wxSize(144,38), 0, 0, 0, wxDefaultValidator, _T("ID_CHOICE1"));
    plot_peaks_type->Append(_("S1 (max dif)"));
    plot_peaks_type->Append(_("S2 (avg of dif)"));
    plot_peaks_type->Append(_("S3 (dif of avg)"));
    plot_peaks_type->SetSelection( plot_peaks_type->Append(_("S4 (Entropy)")) );
    plot_peaks_type->SetToolTip(_("different function for peak finding algorithm"));
    DO_STUFF = new wxButton(this, ID_BUTTON11, _("DO STUFF"), wxPoint(120,480), wxSize(144,24), 0, wxDefaultValidator, _T("ID_BUTTON11"));
    PEAKS = new wxButton(this, ID_BUTTON12, _("Compare"), wxPoint(224,240), wxSize(88,31), 0, wxDefaultValidator, _T("ID_BUTTON12"));
    PEAKS->SetToolTip(_("tries to find peaks and compares with database"));
    PEAKS_epsilon = new wxTextCtrl(this, ID_PEAKS_epsilon, _("0.2"), wxPoint(344,248), wxSize(40,21), 0, wxDefaultValidator, _T("ID_PEAKS_epsilon"));
    PEAKS_epsilon->SetToolTip(_("epsion; max distance to database to identify peak"));
    set_zero = new wxButton(this, ID_set_zero, _("Set Zero"), wxPoint(16,280), wxSize(88,24), 0, wxDefaultValidator, _T("ID_set_zero"));
    set_zero->SetToolTip(_("sets graph to 0 from Start to End"));
    set_zero_start = new wxTextCtrl(this, ID_set_zero_start, _("0"), wxPoint(64,312), wxSize(40,24), 0, wxDefaultValidator, _T("ID_set_zero_start"));
    set_zero_start->SetToolTip(_("startvalue for X axis to set zero"));
    set_zero_end = new wxTextCtrl(this, ID_set_zero_end, _("120"), wxPoint(64,344), wxSize(40,24), 0, wxDefaultValidator, _T("ID_set_zero_end"));
    set_zero_end->SetToolTip(_("endvalue for X axis to set zero"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("End:"), wxPoint(24,344), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText1->SetToolTip(_("endvalue for X axis to set zero"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("Start:"), wxPoint(24,312), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText2->SetToolTip(_("startvalue for X axis to set zero"));
    PEAK_multiplication = new wxButton(this, ID_PEAK_multiplication, _("Graph*Database"), wxPoint(8,384), wxSize(144,40), 0, wxDefaultValidator, _T("ID_PEAK_multiplication"));
    PEAK_multiplication->SetToolTip(_("multiplies graph with all database files to guess which are the most likely"));
    Save_Graph = new wxButton(this, ID_Save_Graph, _("Save Graph"), wxPoint(8,40), wxSize(88,24), 0, wxDefaultValidator, _T("ID_Save_Graph"));
    Save_Graph->SetToolTip(_("saves current graph to .xy file"));
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("K:"), wxPoint(136,120), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    StaticText3->SetToolTip(_("number of points to left/right in the kernel density estimation"));
    standard_format = new wxButton(this, ID_standard_format, _("Standard Format"), wxPoint(216,80), wxSize(160,48), 0, wxDefaultValidator, _T("ID_standard_format"));
    standard_format->SetToolTip(_("formats graphs in a way that works with many inputs"));
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("K:"), wxPoint(40,176), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    StaticText4->SetToolTip(_("number of points to left/right in the intervall"));
    show_again = new wxButton(this, ID_show_again, _("<- show again"), wxPoint(160,384), wxSize(104,40), 0, wxDefaultValidator, _T("ID_show_again"));
    show_again->SetToolTip(_("show output txt file again if new calculation isn\'t necessary"));
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("high:"), wxPoint(24,224), wxSize(40,16), 0, _T("ID_STATICTEXT5"));
    StaticText5->SetToolTip(_("cuts X number of highest points to remove peaks"));
    StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("low:"), wxPoint(112,224), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    StaticText6->SetToolTip(_("removes the X lowest points to balance out the high point removal"));
    epsilon = new wxStaticText(this, ID_STATICTEXT7, _("e:"), wxPoint(320,248), wxSize(16,16), 0, _T("ID_STATICTEXT7"));
    epsilon->SetToolTip(_("epsion; max distance to database to identify peak"));
    StaticText7 = new wxStaticText(this, ID_STATICTEXT8, _("K:"), wxPoint(320,192), wxDefaultSize, 0, _T("ID_STATICTEXT8"));
    StaticText7->SetToolTip(_("number of points to left/right in the intervall"));
    StaticText8 = new wxStaticText(this, ID_STATICTEXT9, _("H:"), wxPoint(320,216), wxDefaultSize, 0, _T("ID_STATICTEXT9"));
    StaticText8->SetToolTip(_("threshhold value to determine peak"));
    StaticBox7 = new wxStaticBox(this, ID_STATICBOX7, _("Manually Add Peaks "), wxPoint(216,280), wxSize(176,80), 0, _T("ID_STATICBOX7"));
    add_peak = new wxButton(this, ID_add_peak, _("Add"), wxPoint(232,328), wxSize(64,23), 0, wxDefaultValidator, _T("ID_add_peak"));
    add_peak->SetToolTip(_("add peak with X and Y value to detected peaks"));
    clear_manual_peaks = new wxButton(this, ID_clear_manual_peaks, _("Clear All"), wxPoint(320,328), wxSize(64,23), 0, wxDefaultValidator, _T("ID_clear_manual_peaks"));
    clear_manual_peaks->SetToolTip(_("clears list of manual inputed peaks"));
    X_man_peak = new wxTextCtrl(this, ID_X_man_peak, wxEmptyString, wxPoint(248,304), wxSize(48,21), 0, wxDefaultValidator, _T("ID_X_man_peak"));
    X_man_peak->SetToolTip(_("X value for manual peak"));
    StaticText9 = new wxStaticText(this, ID_STATICTEXT10, _("X:"), wxPoint(232,304), wxDefaultSize, 0, _T("ID_STATICTEXT10"));
    StaticText9->SetToolTip(_("X value for manual peak"));
    Y_man_peak = new wxTextCtrl(this, ID_Y_man_peak, wxEmptyString, wxPoint(336,304), wxSize(48,21), 0, wxDefaultValidator, _T("ID_Y_man_peak"));
    Y_man_peak->SetToolTip(_("Y value for manual peak"));
    StaticText10 = new wxStaticText(this, ID_STATICTEXT11, _("Y:"), wxPoint(320,304), wxDefaultSize, 0, _T("ID_STATICTEXT11"));
    StaticText10->SetToolTip(_("Y value for manual peak"));
    MenuBar1 = new wxMenuBar();
    Menu3 = new wxMenu();
    Database_OPEN = new wxMenuItem(Menu3, ID_MENUITEM3, _("Open"), _("Shows current database file."), wxITEM_NORMAL);
    Menu3->Append(Database_OPEN);
    Database_RELOAD = new wxMenuItem(Menu3, ID_MENUITEM2, _("Reload"), _("Recreates Database-peak file in case of added files."), wxITEM_NORMAL);
    Menu3->Append(Database_RELOAD);
    MenuBar1->Append(Menu3, _("Database"));
    Menu2 = new wxMenu();
    Help_gnuplot_path = new wxMenuItem(Menu2, ID_MENUITEM1, _("My gnuplot doesn\'t open!"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(Help_gnuplot_path);
    HowToUse = new wxMenuItem(Menu2, ID_MENUITEM4, _("How do I use this app\?"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(HowToUse);
    WhatIsKDE = new wxMenuItem(Menu2, ID_MENUITEM5, _("What is a kernel density estimation\?"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(WhatIsKDE);
    Sourcecode = new wxMenuItem(Menu2, ID_MENUITEM6, _("Where is the sourcecode\?"), wxEmptyString, wxITEM_NORMAL);
    Menu2->Append(Sourcecode);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    Database_RELOAD_INPUT = new wxTextEntryDialog(this, _("Please enter cutoff height for peaks in database(MAX:100 MIN:0):"), _("Reloading Database"), _("10"), wxOK|wxCANCEL|wxCENTRE|wxWS_EX_VALIDATE_RECURSIVELY, wxDefaultPosition);

    Connect(ID_CHECKBOX3,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_plot_Click);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::Ongnuplot_plotClick);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&PA_WXFrame::Ongnuplot_plotClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_plot_Click);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_Load_File_Click);
    Connect(ID_TEXTCTRL3,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&PA_WXFrame::On_Load_File_Click);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_plot_Click);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_N_Norm_Click);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_Back_Button_Click);
    Connect(ID_BUTTON6,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_format_all_Click);
    Connect(ID_BUTTON7,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_remove_noise_Click);
    Connect(ID_TEXTCTRL2,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&PA_WXFrame::On_remove_noise_Click);
    Connect(ID_TEXTCTRL4,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&PA_WXFrame::On_remove_noise_Click);
    Connect(ID_BUTTON8,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::Onremove_backgroundClick);
    Connect(ID_TEXTCTRL5,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&PA_WXFrame::Onremove_backgroundClick);
    Connect(ID_TEXTCTRL6,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&PA_WXFrame::Onremove_backgroundClick);
    Connect(ID_TEXTCTRL7,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&PA_WXFrame::Onremove_backgroundClick);
    Connect(ID_BUTTON9,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_DFT_Click);
    Connect(ID_BUTTON10,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_neg_zero_Click);
    Connect(ID_TEXTCTRL8,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&PA_WXFrame::On_plot_Click);
    Connect(ID_TEXTCTRL9,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&PA_WXFrame::On_plot_Click);
    Connect(ID_CHOICE1,wxEVT_COMMAND_CHOICE_SELECTED,(wxObjectEventFunction)&PA_WXFrame::On_plot_Click);
    Connect(ID_BUTTON11,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_DO_STUFF_Click);
    Connect(ID_BUTTON12,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_PEAKS_Click);
    Connect(ID_PEAKS_epsilon,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&PA_WXFrame::On_PEAKS_Click);
    Connect(ID_set_zero,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_set_zero_Click);
    Connect(ID_set_zero_start,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&PA_WXFrame::On_set_zero_Click);
    Connect(ID_set_zero_end,wxEVT_COMMAND_TEXT_ENTER,(wxObjectEventFunction)&PA_WXFrame::On_set_zero_Click);
    Connect(ID_PEAK_multiplication,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_PEAK_multiplication_Click);
    Connect(ID_Save_Graph,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_Save_Graph_Click);
    Connect(ID_standard_format,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_standard_format_Click);
    Connect(ID_show_again,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_show_again_Click);
    Connect(ID_add_peak,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_add_peak_Click);
    Connect(ID_clear_manual_peaks,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&PA_WXFrame::On_clear_manual_peaks_Click);
    Connect(ID_MENUITEM3,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PA_WXFrame::On_Database_OPEN_Selected);
    Connect(ID_MENUITEM2,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PA_WXFrame::On_Database_RELOAD_Selected);
    Connect(ID_MENUITEM1,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PA_WXFrame::On_Help_gnuplot_path_Selected);
    Connect(ID_MENUITEM4,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PA_WXFrame::On_HowToUse_Selected);
    Connect(ID_MENUITEM5,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PA_WXFrame::On_WhatIsKDE_Selected);
    Connect(ID_MENUITEM6,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&PA_WXFrame::On_Sourcecode_Selected);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&PA_WXFrame::OnClose);
    //*)

    ///Get Program location
    location = boost::dll::program_location().string();
    location = location.substr(0,location.find_last_of("/\\"));
    ///Go to current location
    gp << "cd '" << location << "'\n";
    gp.flush();
}

PA_WXFrame::~PA_WXFrame()
{
    //(*Destroy(PA_WXFrame)
    //*)
}

///FUNCTIONS FOR BUTTONS ETC...

//ease of use definitions
#define GNUPLOT_PLOT_TEXT PA_WXFrame::gnuplot_plot_text->GetValue()
#define LOAD_FILE_TEXT PA_WXFrame::Load_File_Text->GetValue()

#define AUTO_NORM() if(check_auto_N_Norm->IsChecked())graph.MAX_norm(100.0);
#define AUTO_PLOT() if(check_auto_plot->IsChecked())On_plot_Click(event);
#define SAVE() last_graph=graph;

//HELPER FUNCTIONS
inline void Error_Out(const string& err){
    wxMessageBox(_(err), _("Error"),wxOK|wxCENTRE|wxICON_ERROR);
}
////--------------------------


void PA_WXFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void PA_WXFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void PA_WXFrame::OnClose(wxCloseEvent& event)
{
    exit(0);
}

void PA_WXFrame::Ongnuplot_plotClick(wxCommandEvent& event)
{
    gp << GNUPLOT_PLOT_TEXT << "\n";
    gp.flush();
}

//!MAKE IT SO THAT PICKING S FUNCTION CHANGES DEFAULT VALUES

void PA_WXFrame::On_plot_Click(wxCommandEvent& event)
{
    std::ofstream temp("temp.xy");
    temp << graph;
    gp << "plot 'temp.xy'";

    if(plot_peaks->IsChecked()){
        try{
            int K = std::stoi(static_cast<string>(plot_peaks_K->GetValue()));
            double H = std::stod(static_cast<string>(plot_peaks_H->GetValue()));
            int type = plot_peaks_type->GetSelection() + 1; //+1 so that 1 -> S1

            //! negativ values?!
            //!PEAKS SHOULD PROBABLY NOT BE CALCULATED HERE
            ///CALCULATE PEAKS
            std::vector<int> temp_peak_index =  graph.find_peaks(K,H,type);
            peaks.clear();

            ///CONVERT INDEX TO LIST OF X/Y VALUES VECTOR
            for(const auto& ii : temp_peak_index){
                peaks.push_back(std::make_pair(graph.X(ii),graph.Y(ii)));
            }

            ///ADD MANUAL PEAKS
            for(const auto& ii : manual_peaks){
                peaks.push_back(ii);
            }

            ///OUTPUT PEAKS
            std::ofstream temp_peaks("temp_peaks.xy");

            for(const auto& ii : peaks){
                temp_peaks << ii.first << " " << ii.second << std::endl;
            }

        }catch(...){Error_Out("Values are erroneous.");return;}//erroneous is a great word

        gp << ",'temp_peaks.xy' pt 7 ps 1.5";
    }

    gp << '\n';
    gp.flush();
}

void PA_WXFrame::On_Load_File_Click(wxCommandEvent& event)
{
    wxString text(LOAD_FILE_TEXT);
    if(text.IsEmpty()){//opens a file dialog if its empty
        wxFileDialog FileDialog(this, _("Select file to load data from"), "", "", wxFileSelectorDefaultWildcardStr, wxFD_OPEN|wxFD_FILE_MUST_EXIST);
        if (FileDialog.ShowModal() == wxID_CANCEL)return;
        text = FileDialog.GetPath();
    }
    std::ifstream in(text);
    // makes it so "out" works even when in data folder and missing .xy
    if(!in.is_open()){
        while(1){//!BAD CODE BUT I GUESS WHO CARES
        in.open(text+".xy");
        if(in.is_open())break;

        in.open("data/"+text+".xy");
        if(in.is_open())break;

        in.open("data/"+text);
        if(in.is_open())break;

        Error_Out(static_cast<string>("Could not find/open File: " + text));
        return;
        }
    }

    SAVE()

    graph.clear();
    in >> graph;

    AUTO_NORM()
    AUTO_PLOT()
}

void PA_WXFrame::On_N_Norm_Click(wxCommandEvent& event)
{
    SAVE()

    graph.MAX_norm(100.0);

    AUTO_PLOT()
}

void PA_WXFrame::On_Back_Button_Click(wxCommandEvent& event)
{
    //!WE NEED TO GO DEEPER
    Graph temp = graph;
    graph = last_graph;
    last_graph = temp;

    AUTO_NORM()
    AUTO_PLOT()
}

void PA_WXFrame::On_format_all_Click(wxCommandEvent& event)
{
    try{
        double dPhi = std::stod(static_cast<string>(dPhi_textbox->GetValue()));

        SAVE()

        graph.format_ALL(dPhi);
    }
    catch(...){Error_Out("dPhi value is erroneous.");return;}

    AUTO_NORM()
    AUTO_PLOT()
}

void PA_WXFrame::On_remove_noise_Click(wxCommandEvent& event)
{
    try{
        double dPhi = std::stod(static_cast<string>(dPhi_textbox->GetValue()));
        int K = std::stoi(static_cast<string>(remove_noise_K->GetValue()));

        SAVE()

        graph.remove_noise(dPhi,K);
    }
    catch(...){Error_Out("K or dPhi value is erroneous.");return;}

    AUTO_NORM()
    AUTO_PLOT()
}

void PA_WXFrame::Onremove_backgroundClick(wxCommandEvent& event)
{
    try{
        int K = std::stoi(static_cast<string>(remove_background_K->GetValue()));
        int cut_high = std::stoi(static_cast<string>(remove_background_cut_high->GetValue()));
        int cut_low = std::stoi(static_cast<string>(remove_background_cut_low->GetValue()));

        SAVE()

        graph.remove_background(K,cut_high,cut_low);
    }//!BETTER ERROR HANDLING
    catch(...){Error_Out("Values are erroneous.");return;}

    AUTO_NORM()
    AUTO_PLOT()
}

void PA_WXFrame::On_DFT_Click(wxCommandEvent& event)
{
    SAVE()

    if(graph.isFourier){graph.DFT_MT(true);}
    else{graph.DFT_MT();}

    if(graph.isFourier){
        AUTO_NORM()
    }

    graph.isFourier = !graph.isFourier;

    AUTO_PLOT()
}

void PA_WXFrame::On_neg_zero_Click(wxCommandEvent& event)
{
    SAVE()

    graph.neg_zero();

    AUTO_NORM()
    AUTO_PLOT()
}

void PA_WXFrame::On_Database_RELOAD_Selected(wxCommandEvent& event)
{
    std::vector<Graph> data;
    std::vector<int> temp_peaks;
    std::stringstream temp_ss("");
    std::ofstream database("database.txt");
    std::string temp_str;
    Graph temp_graph;

    std::string msg_str;//string for output in message box

    Database_RELOAD_INPUT->ShowModal();

    ///FOR EACH FILE IN DATABASE DIRECTORY
    for (const auto & entry : boost::filesystem::directory_iterator(location+"/data/database")){

        temp_graph.clear();
        temp_peaks.clear();
        temp_ss.str("");

        //convert path to string, i know it's not the best way, fix it if you want
        temp_ss << entry;
        temp_str = temp_ss.str();
        if(temp_str.size() < 6){Error_Out("Could not open file: " + temp_str + "\ntemp_str.size() < 6");return;}
        temp_str = temp_str.substr(1,temp_str.size()-2); //because of "; format is "LOCATION" and it should only be LOCATION
        temp_ss.str("");

        ///LOAD GRAPH FROM FILE

        std::ifstream temp_in(temp_str);
        if(!temp_in.is_open()){Error_Out("Could not open file: " + temp_str);return;}
        temp_in >> temp_graph;

        ///FIND PEAKS IN GRAPH

        //! 0.01 ?!?!?!?!?
        temp_peaks = temp_graph.find_peaks(10,0.01,1);//should hopefully work, it should find any point where neighbors are lower
        //SORTING FOR DESCENDING Y
        auto myCompare = [temp_graph](const int& a, const int& b){return temp_graph.Y(a)>temp_graph.Y(b);};
        std::sort(temp_peaks.begin(),temp_peaks.end(),myCompare);

        ///WRITE PEAKS INTO DATABASE FILE

        //get name of file
        if(temp_str.substr(temp_str.size()-3,temp_str.size()-1) == string(".xy"))temp_str = temp_str.substr(0,temp_str.size()-3);//removes .xy at end
        if(!temp_str.size())throw std::runtime_error("wut, file was named only \".xy\" ?!?!?");
        temp_str = temp_str.substr(temp_str.find_last_of("/\\")+1,temp_str.size()-1); //gets only name of file for clearer reading

        msg_str+=temp_str+'\n';

        double cutoff;
        try{cutoff = std::stod(static_cast<std::string>(Database_RELOAD_INPUT->GetValue()));}
        catch(...){Error_Out("Input was erroneous.\nSet to 25.");cutoff=25;}//25 is arbitrary

        for(const auto& ii : temp_peaks){
            if(temp_graph.Y(ii)< cutoff )continue;
            database << temp_graph.X(ii) << '\t' << temp_graph.Y(ii) << '\t' << temp_str <<'\n';
        }

    }



    wxMessageBox("Database succesfully reloaded.\nFiles Loaded:\n"+msg_str,"Done");

}

void PA_WXFrame::On_Help_gnuplot_path_Selected(wxCommandEvent& event)
{
    wxMessageBox("If you have gnuplot installed check if 'gnuplot' is a valid command line command, if not then add the gnuplot bin folder to your PATH variables.","This may help...");
}

void PA_WXFrame::On_PEAKS_Click(wxCommandEvent& event)
{
    plot_peaks->SetValue(true);
    On_plot_Click(event);//!plotting needs to happen because peaks are calculated there, which is indeed stupid

    //SORTING FOR DESCENDING Y
    auto myCompare = [](const std::pair<double,double>& a, const std::pair<double,double>& b){return a.second>b.second;};
    std::sort(peaks.begin(),peaks.end(),myCompare);

    //FUNCTION FOR SORTING TUPLE VECTOR (NEEDED LATER)
    auto myCompTuple = [](const std::tuple<double,double,std::string>& a, const std::tuple<double,double,std::string>& b){
                            return std::get<1>(a)>std::get<1>(b);};

    ///read in database //! SHOULD MAYBE NOT HAPPEN HERE (EVERY TIME)
    std::ifstream in_database("database.txt");
    double x,y;
    std::string name;
    std::vector<std::tuple<double,double,std::string>> database;
    while(in_database >> x >> y >> name){
        database.push_back(std::make_tuple(x,y,name));
    }

    /// GET GUESSES FROM DATABASE
    std::stringstream ss("");
    ss << "X\tY\tX GUESS\tY GUESS\tGUESS\n";

    double Peak_epsilon;
    try{Peak_epsilon = std::stod(static_cast<std::string>(PEAKS_epsilon->GetValue()));
        if(Peak_epsilon < 0) {Error_Out("Epsilon input was negativ.\nSet to positiv.");Peak_epsilon=-Peak_epsilon;}
    }catch(...){Error_Out("Epsilon input was erroneous.\nSet to 0.2.");Peak_epsilon=0.2;}//0.2 is arbitrary

    double X,Y;
    std::string found_name;
    std::vector<std::tuple<double,double,std::string>> found_matches;
    double xx,yy;//x and y for guess output

    for(const auto& ii : peaks){
        X=ii.first;
        Y=ii.second;
        found_name="NONE";
        found_matches.clear();

        for(const auto& jj : database){
            if(std::abs(std::get<0>(jj)-X)< Peak_epsilon){
                found_name=std::get<2>(jj);
                xx=std::get<0>(jj);
                yy=std::get<1>(jj);

                found_matches.push_back(std::make_tuple(xx,yy,found_name));
           }
        }
        std::sort(found_matches.begin(),found_matches.end(),myCompTuple);

        std::stringstream temp_ss("");
        temp_ss << X << '\t' << Y << '\t';;
        std::string temp_string(temp_ss.str());
        temp_ss << '\n';

        if(found_name!="NONE"){//!I HEREBY DECLARE THAT NO DATA FILE SHALL EVER BE NAMED "NONE"
            std::sort(found_matches.begin(),found_matches.end(),myCompTuple);

            for(const auto& jj : found_matches){
                temp_ss << "\t\t";//!WEIRD HARDCODED FORMATING
                temp_ss << std::get<0>(jj) << '\t' << std::get<1>(jj) << '\t' << std::get<2>(jj) << '\n';
            }
        }


        ss << temp_ss.str() << '\n';
    }



    wxMessageBox(ss.str(),"Found Peaks:",wxOK|wxCENTRE);
}

void PA_WXFrame::On_PEAK_multiplication_Click(wxCommandEvent& event)
{
    std::string temp_str;
    std::stringstream temp_ss("");
    Graph temp_graph;
    std::vector<std::pair<std::string,double>> products;
    std::ofstream products_out("products.txt");

    //FORMAT GRAPH
    graph.format_ALL(0.01);
    graph.MAX_norm(100);

    //FOR EACH FILE IN DATABASE DIRECTORY
    for (const auto & entry : boost::filesystem::directory_iterator(location+"/data/database")){

        temp_graph.clear();
        temp_ss.str("");

        //convert path to string, i know it's not the best way, fix it if you want
        temp_ss << entry;
        temp_str = temp_ss.str();
        if(temp_str.size() < 6){Error_Out("Could not open file: " + temp_str + "\ntemp_str.size() < 6");return;}
        temp_str = temp_str.substr(1,temp_str.size()-2); //because of "; format is "LOCATION" and it should only be LOCATION
        temp_ss.str("");

        ///LOAD GRAPH FROM FILE

        std::ifstream temp_in(temp_str);
        if(!temp_in.is_open()){Error_Out("Could not open file: " + temp_str);return;}
        temp_in >> temp_graph;

        ///NORM IT //!AND REMOVE REALLY LOW POINTS
        temp_graph.format_ALL(0.01);
        temp_graph.norm(1);

        ///CALCULATE PRODUCT (SUM OF ALL Y1 * Y2)
        double sum=0;
        for(int ii=0;ii<graph.size();++ii){
            sum+=graph.Y(ii)*temp_graph.Y(ii);
        }

        ///SAVE PRODUCT

        //get name of file
        if(temp_str.substr(temp_str.size()-3,temp_str.size()-1) == string(".xy"))temp_str = temp_str.substr(0,temp_str.size()-3);//removes .xy at end
        if(!temp_str.size())throw std::runtime_error("wut, file was named only \".xy\" ?!?!?");
        temp_str = temp_str.substr(temp_str.find_last_of("/\\")+1,temp_str.size()-1); //gets only name of file for clearer reading

        products.push_back(std::make_pair(temp_str,sum));
    }
    ///SORT ALL PRODUCTS
    auto myCompare = [](const std::pair<std::string,double>& a, const std::pair<std::string,double>& b){return a.second>b.second;};
    std::sort(products.begin(),products.end(),myCompare);

    ///OUTPUT
    for(const auto& ii : products){
        products_out << ii.second << "\t" << ii.first << '\n';//!
        temp_ss << ii.second << "\t" << ii.first << '\n';
    }

    wxMessageBox(temp_ss.str(),"Done");
}

void PA_WXFrame::On_Database_OPEN_Selected(wxCommandEvent& event)
{
    wxExecute("notepad database.txt");
}




void PA_WXFrame::On_set_zero_Click(wxCommandEvent& event)
{

    int N = graph.size();
    double startPhi,endPhi;
    int startPoint=0,endPoint=N-1;

    try{
    startPhi=std::stod(static_cast<std::string>(set_zero_start->GetValue()));
    endPhi=std::stod(static_cast<std::string>(set_zero_end->GetValue()));
    }catch(...){Error_Out("Values are erroneous.");return;}

    for(int ii=0;ii<N;++ii){//get first point which is higher
        if(graph.X(ii) > startPhi){startPoint=ii;break;}
    }

    for(int ii=startPoint;ii<N;++ii){
        if(graph.X(ii) > endPhi){endPoint=ii;break;}
    }

    SAVE()

    graph.set_zero(startPoint,endPoint);

    AUTO_NORM()
    AUTO_PLOT()
}


void PA_WXFrame::On_DO_STUFF_Click(wxCommandEvent& event)
{
    wxMessageBox("STUFF","DID");
}

void PA_WXFrame::On_Save_Graph_Click(wxCommandEvent& event)
{
    wxFileDialog FileDialog(this, _("Select file to load data from"), "", "", "XY files (*.xy)|*.xy", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (FileDialog.ShowModal() == wxID_CANCEL)return;
    wxString text = FileDialog.GetPath();

    std::ofstream out(text);

    if(!out.is_open()){Error_Out("Could not save file.");return;}
    out << graph;
}

void PA_WXFrame::On_standard_format_Click(wxCommandEvent& event)
{
    SAVE()

    graph.format(0.01);
    graph.remove_noise(0.01,5);
    graph.remove_background(200,200,150);
    graph.format_ALL(0.01);
    graph.neg_zero();

    plot_peaks->SetValue(true);

    AUTO_NORM()
    AUTO_PLOT()
}

void PA_WXFrame::On_show_again_Click(wxCommandEvent& event)
{
    std::system("products.txt");
}

void PA_WXFrame::On_add_peak_Click(wxCommandEvent& event)
{
    try{
        double X = std::stod(static_cast<std::string>(X_man_peak->GetValue()));
        double Y = std::stod(static_cast<std::string>(Y_man_peak->GetValue()));

        manual_peaks.push_back(std::make_pair(X,Y));
    }catch(...){Error_Out("Input was erroneous.");return;}

    AUTO_PLOT()
}
void PA_WXFrame::On_clear_manual_peaks_Click(wxCommandEvent& event)
{
    manual_peaks.clear();

    AUTO_PLOT()
}

void PA_WXFrame::On_HowToUse_Selected(wxCommandEvent& event)
{
    wxExecute("notepad README.txt");
}

void PA_WXFrame::On_WhatIsKDE_Selected(wxCommandEvent& event)
{
    wxLaunchDefaultBrowser("https://mathisonian.github.io/kde/");
}

void PA_WXFrame::On_Sourcecode_Selected(wxCommandEvent& event)
{
    wxLaunchDefaultBrowser("https://github.com/SkipXX/PA_WX");
}
