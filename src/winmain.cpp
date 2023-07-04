

#include "project.h"


#define DEFAULT_OUTPUT_CHANNELS ( ID_DBG_ERROR | ID_DBG_USER_MESSAGES )


unsigned int gDebugging = DEFAULT_OUTPUT_CHANNELS;

HWND hMainWnd = NULL;

BOOL bContinue;


bool WaitForInput( BOOL * pContinue ) {

    MSG Msg;

    *pContinue = false;
    Button_Enable( GetDlgItem( hMainWnd, IDB_CONTINUE ), true );

    for ( ; ! *pContinue ; ) {

        if ( ! GetMessage( &Msg, 0, 0, 0 ) ) {

            TRACE( ID_DBG_MINUTIAE, "ABENDING PROGRAM" EOL );
            return false;

        }

        if ( IsDialogMessage( hMainWnd, &Msg ) ) {

            continue;

        }

        TranslateMessage( &Msg );
        DispatchMessage( &Msg );

    }

    Button_Enable( GetDlgItem( hMainWnd, IDB_CONTINUE ), false );

    return true;

}


LCARDRESULT pokerproc( const class Deck & playerhand, Hands::Hand playerResult, const class Deck & computerhand, Hands::Hand computerResult, Hands::Hand_Equality he, Hands::notification notify, std::vector<int> & discard_cards_reply, void * p ) {

    MainWnd * pDlg = reinterpret_cast<MainWnd *>( p );

    auto print_deck = []( MainWnd * pDlg, unsigned uCtlID, const Deck & deck ) {

        unsigned u = 1;

        for ( auto const & card : deck ) {

            pDlg->setcard( pDlg->m_hDlg, uCtlID, card.get().ID );

            TRACE( ID_DBG_USER_MESSAGES, u << " - " << card.get().rank_name() << " of " << card.get().suit_name() << " (" << card.get().rank << card.get().suit_symbol() << ")" << EOL );

            u++;
            uCtlID++;

        }

    };

    auto enable_controls = []( MainWnd * pDlg, const std::vector<int> & ctls, bool bEnable ) {

        for ( auto ctl : ctls ) {

            EnableWindow( GetDlgItem( pDlg->m_hDlg, ctl ), bEnable );

        }

    };

    const std::vector<int> allcardctls = {

        ALL_CARD_CONTROL_BUTTONS

    };

    const std::vector<int> playercardctls = {

        PLAYER_CARD_CONTROL_IDS

    };

    switch( notify ) {

        case Hands::notification_init: {

                SetDlgItemText( hMainWnd, IDST_COMPUTER_STATUS, TEXT( "" ) );

                SetDlgItemText( hMainWnd, IDST_PLAYER_STATUS, TEXT( "" ) );

                for ( auto ctl : allcardctls ) {

                    pDlg->setcard( pDlg->m_hDlg, ctl, IDBMP_BACK_BLUE );

                }

                enable_controls( pDlg, allcardctls, false );

                SetFocus( hMainWnd );

                if ( ! WaitForInput( &bContinue ) ) {

                    return 0;

                }

            }
            break;

        case Hands::notification_shuffle:

//            MessageBox( HWND_DESKTOP, TEXT( "Shuffle" ), 0, MB_OK );
            break;

        case Hands::notification_deal:


            TRACE( ID_DBG_USER_MESSAGES, EOL "Computer's hand: " << Hands::name( computerResult ) << EOL );
            print_deck( pDlg, IDST_COMPUTERCARD1, computerhand );

            SetDlgItemText( hMainWnd, IDST_COMPUTER_STATUS, Hands::name( computerResult ) );

            TRACE( ID_DBG_USER_MESSAGES, EOL "Your hand: " << Hands::name( playerResult ) << EOL );
            print_deck( pDlg, IDST_PLAYERCARD1, playerhand );

            SetDlgItemText( hMainWnd, IDST_PLAYER_STATUS, Hands::name( playerResult ) );
            break;

        case Hands::notification_discard: {

                TRACE( ID_DBG_USER_MESSAGES, EOL "Which cards do you wish to discard: " EOL );

                pDlg->discard_cards.clear();

                enable_controls( pDlg, playercardctls, true );

                SetFocus( hMainWnd );

                if ( ! WaitForInput( &bContinue ) ) {

                    return 0;

                }

                enable_controls( pDlg, playercardctls, false );

                SetFocus( hMainWnd );

                discard_cards_reply = pDlg->discard_cards;
                pDlg->discard_cards.clear();

            }
            break;

        case Hands::notification_reveal: {

                TRACE( ID_DBG_USER_MESSAGES, EOL "Computer's hand: " << Hands::name( computerResult ) << EOL );
                print_deck( pDlg, IDST_COMPUTERCARD1, computerhand );

                TRACE( ID_DBG_USER_MESSAGES, EOL "Your hand: " << Hands::name( playerResult ) << EOL );
                print_deck( pDlg, IDST_PLAYERCARD1, playerhand );

                TSTRING computer_addendum;
                TSTRING player_addendum;

                switch( he ) {

                    case Hands::Hand_Equality_TrulyEqual:

                        TRACE( ID_DBG_USER_MESSAGES, EOL "Tie!" EOL );
                        computer_addendum.assign( TEXT( " - Tie!" ) );
                        player_addendum.assign( TEXT( " - Tie!" ) );
                        break;

                    case Hands::Hand_Equality_First_Hand_Is_Highest:

                        TRACE( ID_DBG_USER_MESSAGES, EOL "You win!" EOL );
                        player_addendum.assign( TEXT( " - You win!" ) );
                        break;

                    case Hands::Hand_Equality_Second_Hand_Is_Highest:

                        TRACE( ID_DBG_USER_MESSAGES, EOL "Computer wins!" EOL );
                        computer_addendum.assign( TEXT( " - Computer wins!" ) );
                        break;

                    case Hands::Hand_Equality_Unknown:
                        break;

                }

                SetDlgItemText( hMainWnd, IDST_COMPUTER_STATUS, ( Hands::name( computerResult ) + computer_addendum ).c_str() );
                SetDlgItemText( hMainWnd, IDST_PLAYER_STATUS, ( Hands::name( playerResult ) + player_addendum ).c_str() );

                if ( ! WaitForInput( &bContinue ) ) {

                    return 0;

                }

            }
            break;

    }

    return 1;

}


#if defined( __MINGW32__ )

int main( int iArgC, char ** apsArgs ) {

    if ( iArgC > 1 ) {

        int i = atoi( apsArgs[1] );

        if ( 0 != i ) {

            gDebugging = i | DEFAULT_OUTPUT_CHANNELS;

        }

    }

    HINSTANCE hInst = GetModuleHandle( 0 );

#else /* ! __MINGW32__ */
int 
WINAPI
#if defined( _MSC_VER )
__stdcall 
#endif /* _MSC_VER */
#if defined( __unix__ )
_tWinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR /* pszCmdLine */, int /* nCmdShow */ ) {
#else /* ! __unix__ */
#if defined( UNICODE ) || defined( _UNICODE )
wWinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPWSTR /* pszCmdLine */, int /* nCmdShow */ ) {
#else /* ! UNICODE */
CALLBACK WinMain( HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR /* pszCmdLine */, int /* nCmdShow */ ) {
#endif /* ! UNICODE */
#endif /* ! __unix__ */
#endif /* ! __MINGW32__ */

    TRACE( ID_DBG_CHECKPOINT, "Entering process" EOL );

    OutputDebugString( TEXT( "There is only Zuul" ) );

    OutputDebugString( TEXT( "Call application init" ) );
    Win32AppInit( hInst );
    OutputDebugString( TEXT( "Application init returned" ) );

    int DlgID = ( GetSystemMetrics( SM_CYSCREEN ) > GetSystemMetrics( SM_CXSCREEN ) ) ? IDD_MAIN_PORTRAIT : IDD_MAIN_LANDSCAPE;

    if ( 0 == ( hMainWnd = CreateDialogParam( hInst, MAKEINTRESOURCE( DlgID ), HWND_DESKTOP, reinterpret_cast<DLGPROC>( MainWnd::bDlgProc ), reinterpret_cast<LPARAM>( hInst ) ) ) ) {

        MessageBox( HWND_DESKTOP, TEXT( "Couldn't create main dialog" ), 0, MB_OK );
        return -1;

    }

    MainWnd * pDlg = reinterpret_cast<MainWnd *>( SendMessage( hMainWnd, WM_GETUSERDATA, 0, 0 ) );

    TRACE( ID_DBG_CHECKPOINT, "Starting PlayHand with user pointer " << pDlg << EOL );
    for( ; Card::PlayHand( pokerproc, pDlg ); ) {}

    TRACE( ID_DBG_CHECKPOINT, "Exiting process" EOL );

    return 0;

}
