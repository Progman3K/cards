#ifndef __DLG_WND_H__
#define __DLG_WND_H__


#include "dbg_hlp.h"


#if defined(__unix__) && ! defined(__WIN32__)
extern LONG_PTR SetWindowLongPtr(HWND,int,LONG_PTR);
#else /* ! unix */
#include <windows.h>
#endif /* ! unix */


#ifndef GWL_USERDATA
#define GWL_USERDATA        (-21)
#endif /* GWL_USERDATA */


#ifndef WM_GETUSERDATA
#define WM_GETUSERDATA        (WM_USER + 21)
#endif /* WM_GETUSERDATA */


template <class T> class DlgWnd {

    public:

        HWND m_hDlg;

        virtual INT_PTR bUserDlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam ) = 0;

        static T * GetThis( HWND hDlg ) {

            return reinterpret_cast<T *>( GetWindowLongPtr( hDlg, GWL_USERDATA ) );

        }

        static T * SetThis( HWND hDlg, T * pThis ) {

            return reinterpret_cast<T *>( SetWindowLongPtr( hDlg, GWL_USERDATA, (LONG_PTR)pThis ) );

        }

        static INT_PTR CALLBACK bDlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

            T * pThis = GetThis( hDlg );

            if ( 0 == pThis ) {

                pThis = new T;

                if ( 0 == pThis ) {

                    return false;

                }

                pThis->m_hDlg = hDlg;

                SetThis( hDlg, pThis );

            }

            switch( uiMsg ) {

                case WM_GETUSERDATA:

                    TRACE( ID_DBG_MINUTIAE, "Retrieving WINDOW CLASS USER DATA " << pThis << EOL );
                    SetWindowLongPtr( hDlg, DWLP_MSGRESULT, reinterpret_cast<LONG_PTR>( pThis ) );
                    return reinterpret_cast<INT_PTR>( pThis );

#if defined( UNDER_CE ) || defined( linux ) || defined( ANDROID )
                case WM_DESTROY:

                    /* Under Windows CE, the very last message received is WM_DESTROY */
                    BOOL bRet = pThis->bUserDlgProc( hDlg, uiMsg, wParam, lParam );

                    SetThis( hDlg, 0 );

                    delete pThis;

                    return bRet;

#elif defined( WIN32 ) /* ! UNDER_CE */

                case WM_NCDESTROY:

                    /* On regular Windows, the very last message received is WM_NCDESTROY */
                    INT_PTR bRet = pThis->bUserDlgProc( hDlg, uiMsg, wParam, lParam );

                    SetThis( hDlg, 0 );

                    delete pThis;

                    return bRet;
#endif

            }

            return pThis->bUserDlgProc( hDlg, uiMsg, wParam, lParam );

        }

};


#endif /* __DLG_WND_H__ */
