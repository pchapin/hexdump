/****************************************************************************
FILE          : hexdump.c
LAST REVISION : 2005-12-20
SUBJECT       : Program that displays a file's contents in hex.
PROGRAMMER    : Peter Chapin

This file is part of the hexdump learning archive.

Please send comments or bug reports to

     Peter C. Chapin
     Vermont Technical College
     Williston, VT 05495
     PChapin@vtc.vsc.edu
****************************************************************************/

#define STRICT

#include <string.h>
#include <windows.h>
#include <commdlg.h>
#include "hexdump.h"

LRESULT CALLBACK window_procedure( HWND, UINT, WPARAM, LPARAM );

//
// int WinMain()
//
// The main program registers a window class, creates a window, and then goes into a loop to
// dispatch messages on demand.
//
int WINAPI WinMain(
  HINSTANCE instance,           // A handle to this instance of the program.
  HINSTANCE previous_instance,  // A handle to an earlier instance.
  LPSTR     command_line,       // The command line to this program.
  int       command_show        // Defines how this program's windows show.
  )
{
    static char class_name[] = "HexDump";
    HWND        window_handle;   // Type used to hold a window handle.
    MSG         message;         // Type used to hold Windows messages.
    WNDCLASS    the_class;       // Structure used to define a window class.

    the_class.style         = CS_HREDRAW | CS_VREDRAW;
    the_class.lpfnWndProc   = window_procedure;
    the_class.cbClsExtra    = 0;
    the_class.cbWndExtra    = 0;
    the_class.hInstance     = instance;
    the_class.hIcon         = LoadIcon( 0, IDI_APPLICATION );
    the_class.hCursor       = LoadCursor( 0, IDC_ARROW );
    the_class.hbrBackground = (HBRUSH) GetStockObject( WHITE_BRUSH );
    the_class.lpszMenuName  = MAKEINTRESOURCE( MAIN_MENU );
    the_class.lpszClassName = class_name;

    RegisterClass( &the_class );

    // Create a specific instance of the window class named by class_name.
    window_handle = CreateWindow(
      class_name,           // Which type of window should be created?
      "HexDump",            // Text which appears on title bar and under icon.
      WS_OVERLAPPEDWINDOW | WS_VSCROLL,  // Window style.
      CW_USEDEFAULT,        // Horizontal position of window on screen.
      CW_USEDEFAULT,        // Vertical position of window on screen.
      CW_USEDEFAULT,        // Width of window.
      CW_USEDEFAULT,        // Height of window.
      NULL,                 // Handle of parent window.
      NULL,                 // Handle of menu or child window identifier.
      instance,             // Handle of creating program.
      NULL                  // Address of "window creation" data.
    );

    // Display the window we just created.
    ShowWindow( window_handle, command_show );
    UpdateWindow( window_handle );

    while( GetMessage( &message, NULL, 0, 0 ) ) {
        TranslateMessage( &message );
        DispatchMessage( &message );
    }

    return message.wParam;
}


//
// LRESULT window_procedure( )
//
// This function handles all messages sent to this application's window.
//
LRESULT CALLBACK window_procedure(
  HWND   window_handle,  // This procedure might handle many windows.
  UINT   message,        // The message. WM_...
  WPARAM wParam,         // The word sized parameter of the message.
  LPARAM lParam          // The long word sized parameter of the message.
  )
{
    HDC         context_handle;  // Handle to a device context.
    PAINTSTRUCT paint_info;      // Information on the region to redraw.
    RECT        the_rectangle;   // Description of a rectangular region.

    // The following static variables hold information that needs to be kept around between
    // messages. It is nicer to do this than to create global variables.
    //
    static int char_width;   // The size of the desired font.
    static int char_height;  // The size of the desired font.
    static int position;     // Line number of top line in window.

    switch( message ) {

    // When the window is being created, find out things about it.
    case WM_CREATE: {
        TEXTMETRIC text_metrics;

        context_handle = GetDC( window_handle );

        // We need to find the dimensions of the font we want to use.
        SelectObject( context_handle, GetStockObject( ANSI_FIXED_FONT ) );
        GetTextMetrics( context_handle, &text_metrics );
        char_width  = text_metrics.tmAveCharWidth;
        char_height = text_metrics.tmHeight + text_metrics.tmExternalLeading;
        ReleaseDC( window_handle, context_handle );
        return 0;
    }

    // Part of the window client area needs to be redrawn.
    case WM_PAINT:
        context_handle = BeginPaint( window_handle, &paint_info );
        GetClientRect( window_handle, &the_rectangle );
        SelectObject( context_handle, GetStockObject( ANSI_FIXED_FONT ) );

        DrawText(
          context_handle,
          "Hello, World",
          -1,
          &the_rectangle,
          DT_SINGLELINE | DT_CENTER | DT_VCENTER
        );
        // MODIFY HERE!
        //
        // Actually I have to use TextOut() to output the material of interest. Then I have to
        // use SetScrollPos() to set the scroll bar position appropriately.

        EndPaint( window_handle, &paint_info );
        return 0;

    // Deal with the scroll bar thingys.
    case WM_VSCROLL:
        switch( LOWORD( wParam ) ) {
        case SB_LINEUP:
            position--;
            if( position < 0 ) position = 0;
            InvalidateRect( window_handle, 0, FALSE );
            break;

        case SB_LINEDOWN:
            position++;
            // MODIFY HERE!
            //
            // Figure out how large the client area is (in lines) and make sure we don't let the
            // user scroll off the end.
            break;

        case SB_PAGEUP:
            // MODIFY HERE!
            //
            // Subtract the appropriate number of lines from position (how large is the client
            // area again?) and check to be sure we don't go below zero.
            break;

        case SB_PAGEDOWN:
            // MODIFY HERE!
            //
            // Add the appropriate number of lines to position and check to be sure we don't go
            // off the end.
            break;

        case SB_THUMBPOSITION:
            position = HIWORD( wParam );
            InvalidateRect( window_handle, 0, FALSE );
            break;
        }
        return 0;

      // Handle the menu selections.
      case WM_COMMAND:
          switch( wParam ) {
          case MM_OPEN: {

              // Use the Open File common dialog.
              OPENFILENAME filename_information;
              char name_buffer[128], title_buffer[128];

              name_buffer[0] = '\0';

              memset( &filename_information, 0, sizeof( OPENFILENAME ) );
              filename_information.lStructSize     = sizeof( OPENFILENAME );
              filename_information.hwndOwner       = window_handle;
              filename_information.lpstrFilter     = "All Files(*.*)\0*.*\0";
              filename_information.nFilterIndex    = 1;
              filename_information.lpstrFile       = name_buffer;
              filename_information.nMaxFile        = sizeof( name_buffer );
              filename_information.lpstrFileTitle  = title_buffer;
              filename_information.nMaxFileTitle   = sizeof( title_buffer );
              filename_information.lpstrInitialDir = 0;
              filename_information.Flags =
                OFN_SHOWHELP | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

              // Interact with the user. If we can't get a name, display an error.
              if( GetOpenFileName( &filename_information ) == FALSE ) {
                  MessageBox( window_handle,
                    "No valid file selected", "Open Error", MB_ICONEXCLAMATION );
              }
              else {
                  MessageBox(
                    window_handle,
                    name_buffer,
                    "Selected File",
                    MB_ICONINFORMATION
                  );
                // MODIFY HERE!
                // 
                // Actually here I have to read the file and figure out how many lines it has.
                // Then I have to initialize position, set the scroll bar ranges with SetScroll
                // Range(), and invalidate the rectange with Invalidate Rect() so that a
                // WM_PAINT message will be sent to my window.
              }
          }
              break;

          case MM_SAVE:
              MessageBox( window_handle, "Not implemented", "Sorry", MB_ICONEXCLAMATION );
            break;

          case MM_SAVEAS:
              MessageBox( window_handle, "Not implemented", "Sorry", MB_ICONEXCLAMATION );
            break;

          case MM_EXIT:
              DestroyWindow( window_handle );
              break;

          case MM_HELP:
              MessageBox( window_handle, "No help available", "Sorry", MB_ICONEXCLAMATION );
              break;
          }
          return 0;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        return 0;
    }

    return DefWindowProc( window_handle, message, wParam, lParam );
}
