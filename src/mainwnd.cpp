

#include "project.h"


void MainWnd::OnClose( HWND hWnd ) {

    PostQuitMessage( 0 );
    DestroyWindow( hWnd );

}


void MainWnd::setcard( HWND hWnd, int iCtlID, int CardID ) {

    HWND hCtlWnd = GetDlgItem( hWnd, iCtlID );

    if ( hCtlWnd ) {

        SetWindowLongPtr( hCtlWnd, GWLP_USERDATA, (LONG_PTR)reinterpret_cast<LONG>( MAKELONG( CardID, 0 ) ) );

#if 0
        HBITMAP hBmp = LoadBitmap( hInst, MAKEINTRESOURCE( CardID ) );

//        HANDLE hBmp = LoadImage( hInst, MAKEINTRESOURCE( CardID ), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR );

        if ( 0 != hBmp ) {

            SendMessage( hWnd, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp );

        }
#endif
        InvalidateRect( hCtlWnd, 0, true );

    }

}


BOOL MainWnd::OnInit( HWND hWnd, HWND /* hFocusWnd */, LPARAM lParam ) {

    hInst = reinterpret_cast<HINSTANCE>( lParam );

    portrait.Record( hInst, MAKEINTRESOURCE( IDD_MAIN_PORTRAIT ), hWnd );
    landscape.Record( hInst, MAKEINTRESOURCE( IDD_MAIN_LANDSCAPE ), hWnd );

    SetFocus( GetDlgItem( hWnd, IDB_CONTINUE ) );

    return (BOOL)false;

}


void MainWnd::DrawButton( HWND hWnd, HDC hDC ) {

    int iCtrlID = GetDlgCtrlID( hWnd );

    if ( 0 == iCtrlID ) {

//        TRACE( ID_DBG_ERROR, "ERROR: UNABLE TO DETERMINE CONTROL ID" EOL );
        return;

    }

    int CardID = LOWORD( GetWindowLongPtr( hWnd, GWLP_USERDATA ) );

    if ( 0 == CardID ) {

//        TRACE( ID_DBG_ERROR, "ERROR: NO CARD SET IN CONTROL ID " << iCtrlID << EOL );
        return;

    }

    HBITMAP hBmp = LoadBitmap( hInst, MAKEINTRESOURCE( CardID ) );

    if ( 0 == hBmp ) {

        TRACE( ID_DBG_ERROR, "ERROR: UNABLE TO LOAD BITMAP " << CardID << " error " << GetLastError() << EOL );
        return;

    }

    RECT r;
    GetClientRect( hWnd, &r );

    BITMAP bm;
    GetObject( hBmp, sizeof( bm ), &bm );

    auto hdcMem = CreateCompatibleDC( hDC );

    if ( hdcMem ) {

        auto hOldBmp = SelectBitmap( hdcMem, hBmp );

        StretchBlt( hDC, 0, 0, r.right, r.bottom, hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY );

        switch( iCtrlID ) {

            case IDST_PLAYERCARD1:
            case IDST_PLAYERCARD2:
            case IDST_PLAYERCARD3:
            case IDST_PLAYERCARD4:
            case IDST_PLAYERCARD5:

                int cardno = ( 1 + ( iCtrlID - IDST_PLAYERCARD1 ) );

                if ( discard_cards.end() != std::find ( discard_cards.begin(), discard_cards.end(), cardno ) ) {

                    TRACE( ID_DBG_MINUTIAE, "Draw card reversed" EOL );
                    InvertRect( hDC, &r );
//        HBRUSH hRedBrush = CreateSolidBrush( RGB( 255, 0, 0 ) );
//        FillRect( hDC, &r, hRedBrush );
//        DeleteBrush( hRedBrush );

                }
                break;

        }

        SelectBitmap( hdcMem, hOldBmp );

        DeleteDC( hdcMem );

    }

    DeleteObject( hBmp );

}


void MainWnd::OnDrawItem( HWND hWnd, const DRAWITEMSTRUCT * lpcDI ) {

    TRACE( ID_DBG_MINUTIAE, "DrawItemStruct - CtlType: " << lpcDI->CtlType << " CtlID: " << lpcDI->CtlID << " itemID: " << lpcDI->itemID << " itemAction: " << lpcDI->itemAction << " itemState: " << lpcDI->itemState << " hwndItem: " << lpcDI->hwndItem << " hDC: " << lpcDI->hDC << " rcItem: " << lpcDI->rcItem.left << "," << lpcDI->rcItem.top << "," << lpcDI->rcItem.right << "," << lpcDI->rcItem.bottom << " itemData: " << lpcDI->itemData << EOL );

    DrawButton( lpcDI->hwndItem, lpcDI->hDC );

    if ( ODA_FOCUS & lpcDI->itemAction ) {

        RECT r;

        r = lpcDI->rcItem;

        r.left   += GetSystemMetrics( SM_CXEDGE );
        r.top    += GetSystemMetrics( SM_CXEDGE );
        r.right  -= GetSystemMetrics( SM_CXEDGE );
        r.bottom -= GetSystemMetrics( SM_CXEDGE );

        DrawFocusRect( lpcDI->hDC, &r );

    }

}

#if 0
HBRUSH MainWnd::OnCtlColorButton( HWND hWnd, HDC hDC, HWND hChildWnd, int type ) {

    DrawButton( hChildWnd, hDC );

    SetDlgMsgResult( hWnd, WM_CTLCOLORBTN, 0 );

    return 0;

}
#endif

INT_PTR MainWnd::bUserDlgProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

    switch( uiMsg ) {

        case WM_CLOSE:

            HANDLE_WM_CLOSE( hWnd, wParam, lParam, OnClose );
            break;

        case WM_COMMAND:

            HANDLE_WM_COMMAND( hWnd, wParam, lParam, OnCommand );
            break;
#if 0
        case WM_CTLCOLORBTN:

            HANDLE_WM_CTLCOLORBTN( hWnd, wParam, lParam, OnCtlColorButton );
            break;
#endif
        case WM_DISPLAYCHANGE:

            HANDLE_WM_DISPLAYCHANGE( hWnd, wParam, lParam, OnDisplayChange );
            return (INT_PTR)false; /* Default handler must process this also. */

        case WM_DRAWITEM:

            HANDLE_WM_DRAWITEM( hWnd, wParam, lParam, OnDrawItem );
            break;

//        case WM_ERASEBKGND:
//            break;

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
