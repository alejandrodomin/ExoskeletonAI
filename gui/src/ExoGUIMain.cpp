/***************************************************************
 * Name:      ExoGUIMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Alejandro Dominguez (adomi120@fiu.edu)
 * Created:   2018-03-25
 * Copyright: Alejandro Dominguez ()
 * License:
 **************************************************************/

#include "ExoGUIMain.hpp"
#include <wx/msgdlg.h>

//(*InternalHeaders(ExoGUIFrame)
#include <wx/string.h>
#include <wx/intl.h>
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

//(*IdInit(ExoGUIFrame)
const long ExoGUIFrame::ID_BUTTON1 = wxNewId();
const long ExoGUIFrame::ID_SLIDER1 = wxNewId();
const long ExoGUIFrame::ID_PANEL2 = wxNewId();
const long ExoGUIFrame::ID_GAUGE1 = wxNewId();
const long ExoGUIFrame::ID_COMBOBOX1 = wxNewId();
const long ExoGUIFrame::ID_COMBOBOX2 = wxNewId();
const long ExoGUIFrame::ID_STATICTEXT1 = wxNewId();
const long ExoGUIFrame::ID_STATICTEXT2 = wxNewId();
const long ExoGUIFrame::ID_STATICTEXT3 = wxNewId();
const long ExoGUIFrame::ID_PANEL1 = wxNewId();
const long ExoGUIFrame::idMenuQuit = wxNewId();
const long ExoGUIFrame::idMenuAbout = wxNewId();
const long ExoGUIFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ExoGUIFrame,wxFrame)
    //(*EventTable(ExoGUIFrame)
    //*)
END_EVENT_TABLE()

ExoGUIFrame::ExoGUIFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(ExoGUIFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    SetClientSize(wxSize(450,365));
    Panel1 = new wxPanel(this, ID_PANEL1, wxPoint(208,200), wxSize(450,360), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    Button1 = new wxButton(Panel1, ID_BUTTON1, _("Start"), wxPoint(336,312), wxSize(104,29), 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Slider1 = new wxSlider(Panel1, ID_SLIDER1, 0, 1, 10, wxPoint(336,32), wxSize(104,27), 0, wxDefaultValidator, _T("ID_SLIDER1"));
    Panel2 = new wxPanel(Panel1, ID_PANEL2, wxPoint(0,0), wxSize(320,304), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    Gauge1 = new wxGauge(Panel1, ID_GAUGE1, 100, wxPoint(8,312), wxSize(304,28), 0, wxDefaultValidator, _T("ID_GAUGE1"));
    ComboBox1 = new wxComboBox(Panel1, ID_COMBOBOX1, wxEmptyString, wxPoint(336,96), wxSize(105,29), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX1"));
    ComboBox2 = new wxComboBox(Panel1, ID_COMBOBOX2, wxEmptyString, wxPoint(336,160), wxSize(105,29), 0, 0, 0, wxDefaultValidator, _T("ID_COMBOBOX2"));
    StaticText1 = new wxStaticText(Panel1, ID_STATICTEXT1, _("Loop Amount"), wxPoint(336,8), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText2 = new wxStaticText(Panel1, ID_STATICTEXT2, _("Species Select"), wxPoint(336,72), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText3 = new wxStaticText(Panel1, ID_STATICTEXT3, _("Network Select"), wxPoint(336,136), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ExoGUIFrame::OnButton1Click);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ExoGUIFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ExoGUIFrame::OnAbout);
    //*)
}

ExoGUIFrame::~ExoGUIFrame()
{
    if(life != NULL){
        delete life;
        life = NULL;
    }
}

void ExoGUIFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void ExoGUIFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void ExoGUIFrame::OnButton1Click(wxCommandEvent& event)
{
  life = new Ecosystem(5, 5);

  int range = Slider1->GetValue();

  for(int i = 0; i < range; i++){
    life->live();
    Gauge1->SetValue(((float)i/range)*100);
  }
  Gauge1->SetValue(100);
}

void ExoGUIFrame::OnComboBox1Selected(wxCommandEvent& event)
{
}

void ExoGUIFrame::OnComboBox2Selected(wxCommandEvent& event)
{
}