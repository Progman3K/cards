#ifndef __H_ABOUT_H__
#define __H_ABOUT_H__


#include <windowsx.h>

#include "dlgwnd.h"


#include "resource.h"


class AboutWnd : public DlgWnd<AboutWnd> {

        void OnClose( HWND hWnd ) {

            EndDialog( hWnd, 0 );

        }

        void OnCommand( HWND hWnd, int iID, HWND /* hCtlWnd */, UINT /* uiNotifyCode */ ) {

            switch( iID ) {

                case IDCANCEL:

                    FORWARD_WM_CLOSE( hWnd, PostMessage );
                    break;

            }

        }

        BOOL OnInit( HWND hWnd, HWND hFocusWnd, LPARAM lParam );

    public:

        virtual ~AboutWnd() {}

        INT_PTR bUserDlgProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) override {

            switch( uiMsg ) {

                case WM_CLOSE:

                    HANDLE_WM_CLOSE( hWnd, wParam, lParam, OnClose );
                    break;

                case WM_COMMAND:

                    HANDLE_WM_COMMAND( hWnd, wParam, lParam, OnCommand );
                    break;

                case WM_INITDIALOG:

                    HANDLE_WM_INITDIALOG( hWnd, wParam, lParam, OnInit );
                    break;

                default:

                    return (INT_PTR)false;

            }

            return (INT_PTR)true;

        }

};


#endif /* __H_ABOUT_H__ */
