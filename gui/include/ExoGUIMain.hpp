/***************************************************************
 * Name:      ExoGUIMain.h
 * Purpose:   Defines Application Frame
 * Author:    Alejandro Dominguez (adomi120@fiu.edu)
 * Created:   2018-03-25
 * Copyright: Alejandro Dominguez ()
 * License:
 **************************************************************/

#ifndef EXOGUIMAIN_H
#define EXOGUIMAIN_H

//(*Headers(ExoGUIFrame)
#include <wx/gauge.h>
#include <wx/combobox.h>
#include <wx/button.h>
#include <wx/menu.h>
#include <wx/panel.h>
#include <wx/slider.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/stattext.h>
//*)

#include <ecosystem.hpp>

class ExoGUIFrame: public wxFrame
{
    public:

        ExoGUIFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~ExoGUIFrame();

    private:

        //(*Handlers(ExoGUIFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnComboBox1Selected(wxCommandEvent& event);
        void OnComboBox2Selected(wxCommandEvent& event);
        //*)

        //(*Identifiers(ExoGUIFrame)
        static const long ID_BUTTON1;
        static const long ID_SLIDER1;
        static const long ID_PANEL2;
        static const long ID_GAUGE1;
        static const long ID_COMBOBOX1;
        static const long ID_COMBOBOX2;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long ID_PANEL1;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(ExoGUIFrame)
        wxPanel* Panel1;
        wxStatusBar* StatusBar1;
        wxButton* Button1;
        wxStaticText* StaticText1;
        wxPanel* Panel2;
        wxStaticText* StaticText3;
        wxComboBox* ComboBox1;
        wxComboBox* ComboBox2;
        wxStaticText* StaticText2;
        wxSlider* Slider1;
        wxGauge* Gauge1;
        //*)

        Ecosystem *life;

        DECLARE_EVENT_TABLE()
};

#endif // EXOGUIMAIN_H
