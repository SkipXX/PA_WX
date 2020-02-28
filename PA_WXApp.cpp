/***************************************************************
 * Name:      PA_WXApp.cpp
 * Purpose:   Code for Application Class
 * Author:     ()
 * Created:   2020-02-12
 * Copyright:  ()
 * License:
 **************************************************************/

#include "PA_WXApp.h"

//(*AppHeaders
#include "PA_WXMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(PA_WXApp);

bool PA_WXApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;

    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	PA_WXFrame* Frame = new PA_WXFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
