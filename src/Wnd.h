#ifndef __WND_H__
#define	__WND_H__


/*

	Light-weight replacement for MFC or other window-object frameworks.
	Author: J. (Jean-Claude Gervais)

*/
#include <windows.h>
#include <windowsx.h>


template <class T> class Wnd {

	public:

		/*
			To use this class, the programmer must derive his/her window-class from this one.

			This will have the effect of the making all messages received in the lUserWndProc
			arrive in the context of the instance of the class that was derived.

			This class is faster than the equivalent in MFC and does not require any link-time dependancies.

		*/
		virtual LRESULT lUserWndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) = 0;

		static T * GetThis( HWND hWnd ) {

			return (T *)GetWindowLongPtr( hWnd, GWLP_USERDATA );

		}

		static T * SetThis( HWND hWnd, T * pThis ) {

			return (T *)SetWindowLongPtr( hWnd, GWLP_USERDATA, pThis );

		}

		static	LRESULT APIENTRY lWndProc( HWND hWnd, UINT uiMsg, WPARAM wParam, LPARAM lParam ) {

			LRESULT	l;

			T * pThis = GetThis( hWnd );

			if ( NULL == pThis ) {

				pThis = new T;

				if ( NULL == pThis ) {

					return DefWindowProc( hWnd, uiMsg, wParam, lParam );

				}

				pThis->m_hWnd = hWnd;

				SetThis( hWnd, pThis );

			}

			switch( uiMsg ) {

		#ifdef UNDER_CE
				case WM_DESTROY:

					/* Under Windows CE, the very last message received is WM_DESTROY */
					l = pThis->lUserWndProc( hWnd, uiMsg, wParam, lParam );

					SetThis( hWnd, NULL );

					delete pThis;

					return l;
		#endif

		#ifndef UNDER_CE
				case WM_NCDESTROY:

					/* On regular Windows, the very last message received is WM_NCDESTROY */
					l = pThis->lUserWndProc( hWnd, uiMsg, wParam, lParam );

					SetThis( hWnd, NULL );

					delete pThis;

					return l;
		#endif

			}

			return pThis->lUserWndProc( hWnd, uiMsg, wParam, lParam );

		}

	private:

		HWND	m_hWnd;

};


#endif /* __WND_H__ */
