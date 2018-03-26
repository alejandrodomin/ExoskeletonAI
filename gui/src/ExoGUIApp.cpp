/***************************************************************
 * Name:      ExoGUIApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Alejandro Dominguez (adomi120@fiu.edu)
 * Created:   2018-03-25
 * Copyright: Alejandro Dominguez ()
 * License:
 **************************************************************/

#include "ExoGUIApp.hpp"

//(*AppHeaders
#include "ExoGUIMain.hpp"
#include <wx/image.h>
//*)

IMPLEMENT_APP(ExoGUIApp);

bool ExoGUIApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	ExoGUIFrame* Frame = new ExoGUIFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
