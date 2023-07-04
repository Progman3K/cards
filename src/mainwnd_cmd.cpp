

#include "project.h"


void MainWnd::togglecardchoice( HWND hCtlWnd, int cardno ) {

    unsigned short cardID = LOWORD( GetWindowLongPtr( hCtlWnd, GWLP_USERDATA ) );
    TRACE( ID_DBG_MINUTIAE, EOL "Card " << cardno << " (" << cardID << ") requesting discard" EOL );

    // Check if the card # is already in the array.
    auto p = std::find ( discard_cards.begin(), discard_cards.end(), cardno );

    if ( p != discard_cards.end() ) {

        // It is
        TRACE( ID_DBG_MINUTIAE, "Card found in discard vector: " << *p << EOL );

        discard_cards.erase( p );

    } else {

        // if it isn't, add it to the array and paint the control to indicate it is unselected
        TRACE( ID_DBG_MINUTIAE, "Card " << cardno << " not found in discard vector" EOL );
        discard_cards.push_back( cardno );

    }

    // sort the array
    std::sort( discard_cards.begin(), discard_cards.end() );

    InvalidateRect( hCtlWnd, 0, true );

}


void MainWnd::OnCommand( HWND hWnd, int iID, HWND hCtlWnd, UINT uiNotifyCode ) {


    switch( iID ) {

        case IDB_CONTINUE:

            if ( BN_CLICKED == uiNotifyCode ) {

                bContinue = true;

            }
            break;

        case IDCANCEL:
        case IDM_EXIT:

            TRACE( ID_DBG_MINUTIAE, "Command code " << iID << " received, exiting dialog" << EOL );
            FORWARD_WM_CLOSE( hWnd, PostMessage );
            break;

        case IDM_HELP:

            DialogBox( hInst, MAKEINTRESOURCE( IDD_ABOUT ), hWnd, (DLGPROC)AboutWnd::bDlgProc );
            break;

        case IDST_PLAYERCARD1:
        case IDST_PLAYERCARD2:
        case IDST_PLAYERCARD3:
        case IDST_PLAYERCARD4:
        case IDST_PLAYERCARD5: {

                int cardno = ( 1 + ( iID - IDST_PLAYERCARD1 ) );

                togglecardchoice( hCtlWnd, cardno );

            }
            break;

    }

}
