/***************************************************************
 * Name   : wxHexdumpMain.h
 * Purpose: Defines Application Frame
 * Author : Peter C. Chapin (Peter.Chapin@vtc.vsc.edu)
 **************************************************************/

#ifndef WXHELLOMAIN_H
#define WXHELLOMAIN_H

#include <wx/wx.h>

#include "wxHexdumpApp.h"

class wxHexdumpFrame : public wxFrame {
 public:
    wxHexdumpFrame( wxFrame *frame, const wxString &title );
   ~wxHexdumpFrame( );

 private:
   enum {
       idMenuOpen = 1000,
       idMenuQuit,
       idMenuAbout
   };

   void OnClose( wxCloseEvent   &event );
   void OnOpen ( wxCommandEvent &event );
   void OnQuit ( wxCommandEvent &event );
   void OnAbout( wxCommandEvent &event );
   void OnPaint( wxPaintEvent   &event );
   DECLARE_EVENT_TABLE( )
};


#endif
