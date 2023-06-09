

#include "project.h"


void MainWnd::OnClose( HWND hWnd ) {

    DestroyWindow( hWnd );
    PostQuitMessage( 0 );

}


void MainWnd::setcard( HWND hWnd, int iCtlID, int CardID ) {

    HWND hCtlWnd = GetDlgItem( hWnd, iCtlID );

    if ( hCtlWnd ) {

        SetWindowLongPtr( hCtlWnd, GWLP_USERDATA, CardID );
        InvalidateRect( hCtlWnd, 0, true );

    }

}


BOOL MainWnd::OnInit( HWND hWnd, HWND /* hFocusWnd */, LPARAM lParam ) {

    hInst = reinterpret_cast<HINSTANCE>( lParam );

    portrait.Record( hInst, MAKEINTRESOURCE( IDD_MAIN_PORTRAIT ), hWnd );
    landscape.Record( hInst, MAKEINTRESOURCE( IDD_MAIN_LANDSCAPE ), hWnd );

    return (BOOL)true;

}


void MainWnd::OnDrawItem( HWND hWnd, const DRAWITEMSTRUCT * lpcDI ) {

    int CardID = GetWindowLongPtr( lpcDI->hwndItem, GWLP_USERDATA );

    HBITMAP hBmp = LoadBitmap( hInst, MAKEINTRESOURCE( CardID ) );

    RECT r;
    GetClientRect( lpcDI->hwndItem, &r );

    BITMAP bm;
    GetObject( hBmp, sizeof( bm ), &bm );

    auto hdcMem = CreateCompatibleDC( lpcDI->hDC );

    if ( hdcMem ) {

        SelectBitmap( hdcMem, hBmp );

        StretchBlt( lpcDI->hDC, 0, 0, r.right, r.bottom, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY );

        switch( lpcDI->CtlID ) {

            case IDST_PLAYERCARD1:
            case IDST_PLAYERCARD2:
            case IDST_PLAYERCARD3:
            case IDST_PLAYERCARD4:
            case IDST_PLAYERCARD5:

                int cardno = ( 1 + ( lpcDI->CtlID - IDST_PLAYERCARD1 ) );

                if ( discard_cards.end() != std::find ( discard_cards.begin(), discard_cards.end(), cardno ) ) {

                    InvertRect( lpcDI->hDC, &r );

                }
                break;

        }

        DeleteDC( hdcMem );

    }

}


INT_PTR MainWnd::bUserDlgProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    switch( uiMsg ) {

        case WM_CLOSE:

            HANDLE_WM_CLOSE( hWnd, wParam, lParam, OnClose );
            break;

        case WM_COMMAND:

            HANDLE_WM_COMMAND( hWnd, wParam, lParam, OnCommand );
            break;

        case WM_DISPLAYCHANGE:

            HANDLE_WM_DISPLAYCHANGE( hWnd, wParam, lParam, OnDisplayChange );
            return (INT_PTR)false; /* Default handler must process this also. */

        case WM_DRAWITEM:

            HANDLE_WM_DRAWITEM( hWnd, wParam, lParam, OnDrawItem );
            break;

        case WM_GETICON:

            return (INT_PTR)LoadIcon( GetWindowInstance( hWnd ), MAKEINTRESOURCE( IDI_MAIN ) );

        case WM_INITDIALOG:

            HANDLE_WM_INITDIALOG( hWnd, wParam, lParam, OnInit );
            break;

        default:

            return (INT_PTR)false;

    }

    return (INT_PTR)true;

}
