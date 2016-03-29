/***************************************************************
 * Name   : wxHexdumpMain.cpp
 * Purpose: Code for Application Frame
 * Author : Peter C. Chapin (PChapin@vtc.vsc.edu)
 **************************************************************/

#include <wx/filedlg.h>
#include "wxHexdumpMain.h"

// Helper functions.
enum wxbuildinfoformat {
    Short_Format,
    Long_Format
};

wxString wxbuildinfo( wxbuildinfoformat format )
{
    wxString wxbuild( wxVERSION_STRING );

    if( format == Long_Format ) {
        #if defined( __WXMSW__ )
            wxbuild << wxT( "-Windows" );
        #elif defined( __WXMAC__ )
            wxbuild << wxT( "-Mac" );
        #elif defined( __UNIX__ )
            wxbuild << wxT( "-Linux" );
        #endif

        #if wxUSE_UNICODE
            wxbuild << wxT( "-Unicode build" );
        #else
            wxbuild << wxT( "-ANSI build" );
        #endif
    }

    return wxbuild;
}


BEGIN_EVENT_TABLE(wxHexdumpFrame, wxFrame)
    EVT_CLOSE(wxHexdumpFrame::OnClose)
    EVT_MENU(idMenuOpen,  wxHexdumpFrame::OnOpen )
    EVT_MENU(idMenuQuit,  wxHexdumpFrame::OnQuit )
    EVT_MENU(idMenuAbout, wxHexdumpFrame::OnAbout)
    EVT_PAINT(wxHexdumpFrame::OnPaint)
END_EVENT_TABLE()


wxHexdumpFrame::wxHexdumpFrame( wxFrame *frame, const wxString &title ) :
    wxFrame( frame, -1, title )
{
    #if wxUSE_MENUS
    wxMenuBar *mbar = new wxMenuBar( );
    wxMenu *file_menu = new wxMenu( wxT("") );
    file_menu->Append( idMenuOpen, wxT("&Open"), wxT("Open a file") );
    file_menu->Append( idMenuQuit, wxT("&Quit\tAlt-F4"), wxT("Quit wxHexdump") );
    mbar->Append( file_menu, wxT("&File") );

    wxMenu *help_menu = new wxMenu( wxT("") );
    help_menu->Append( idMenuAbout, wxT("&About\tF1"), wxT("Show information about wxHexdump") );
    mbar->Append( help_menu, wxT("&Help") );

    SetMenuBar( mbar );
    #endif

    #if wxUSE_STATUSBAR
    CreateStatusBar( 2 );
    SetStatusText( wxT("Hello wxWidgets user!"), 0 );
    SetStatusText( wxbuildinfo(Short_Format), 1 );
    #endif
}


wxHexdumpFrame::~wxHexdumpFrame( )
{
}


void wxHexdumpFrame::OnClose( wxCloseEvent &event )
{
    Destroy( );
}


void wxHexdumpFrame::OnOpen( wxCommandEvent &event )
{
    wxString caption  = wxT( "File to Open" );
    wxString wildcard = wxT( "All files (*.*)|*.*" );
    wxString default_directory = wxT( "." );
    wxString default_filename  = wxEmptyString;

    wxFileDialog dialog( this, caption, default_directory, default_filename, wildcard );
    if( dialog.ShowModal( ) == wxID_OK ) {
        wxString path = dialog.GetPath( );
        wxMessageBox( path, wxT("Selected path") );
    }
}


void wxHexdumpFrame::OnQuit( wxCommandEvent &event )
{
    Destroy( );
}


void wxHexdumpFrame::OnAbout( wxCommandEvent &event )
{
    wxString msg = wxbuildinfo( Long_Format );
    wxMessageBox( msg, wxT("Welcome to...") );
}


void wxHexdumpFrame::OnPaint( wxPaintEvent &event )
{
    wxPaintDC dc( this );
    wxPoint point( 0, 0 );
    wxSize skip( 0, 14 );
    wxFont font( 12, wxFONTFAMILY_TELETYPE, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL );

    dc.SetFont( font );
    dc.DrawText( wxT( "Hello, World!" ), point );
    point = point + skip;
    dc.DrawText( wxT( "Goodbye, World!" ), point );
}
