/***************************************************************
 * Name:      PA_WXApp.h
 * Purpose:   Defines Application Class
 * Author:     ()
 * Created:   2020-02-12
 * Copyright:  ()
 * License:
 **************************************************************/

#ifndef PA_WXAPP_H
#define PA_WXAPP_H

#include <wx/app.h>

class PA_WXApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // PA_WXAPP_H
