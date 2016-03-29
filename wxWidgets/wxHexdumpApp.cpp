/***************************************************************
 * Name   : wxHexdumpApp.cpp
 * Purpose: Code for Application Class
 * Author : Peter C. Chapin (PChapin@vtc.vsc.edu)
 **************************************************************/

#include "wxHexdumpApp.h"
#include "wxHexdumpMain.h"

IMPLEMENT_APP(wxHexdumpApp);

bool wxHexdumpApp::OnInit( )
{
    wxHexdumpFrame *frame = new wxHexdumpFrame( nullptr, wxT("wxHexdump") );
    // frame->SetIcon( wxICON( main_icon ) );
    frame->Show( );

    return true;
}
