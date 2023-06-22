#ifndef __H_MAINWND_H__
#define __H_MAINWND_H__



#include <tchar.h>
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>

#include <map>
#include <vector>

#include "tstring.h"

#include "dlgwnd.h"
#include "resource.h"
#include "dialoginfo.h"


#define HANDLE_WM_LANGUAGECHANGE(hWnd,wParam,lParam,fn) ((fn)((hWnd),(unsigned)(wParam),lParam),(LRESULT)0)
#define FORWARD_WM_LANGUAGECHANGE(hWnd,lid,lParam,fn) (void)(fn)((hWnd),WM_LANGUAGECHANGE,(WPARAM)(lid),(LPARAM)(lParam))


#ifndef HANDLE_WM_DISPLAYCHANGE
/* void Cls_OnDisplayChange(HWND hwnd, UINT bitsPerPixel, UINT cxScreen, UINT cyScreen) */
#define HANDLE_WM_DISPLAYCHANGE(hwnd, wParam, lParam, fn) ((fn)((hwnd), (UINT)(wParam), (UINT)LOWORD(lParam), (UINT)HIWORD(lParam)), 0L)
#endif


class MainWnd : public DlgWnd<MainWnd> {

        typedef std::pair<int,unsigned> language;
        typedef std::map<int,unsigned> Language;
        Language Languages;

        DialogInfo portrait;
        DialogInfo landscape;

        /* Message-crackers AKA message-handlers */
        void OnClose( HWND );
        void OnCommand( HWND, int, HWND, UINT );
        void OnDisplayChange( HWND, UINT, UINT, UINT );
        void OnDrawItem( HWND, const DRAWITEMSTRUCT * );
        BOOL OnInit( HWND, HWND, LPARAM );
        void OnLanguageChange( HWND, unsigned, LPARAM );

        /* Functions */
        void InitLanguage( HWND hWnd );

        void TransferToUI( HWND hWnd );

        void Continue( HWND hWnd );

        TSTRING currentlanguage;

        void SetWindowTitle( HWND hWnd );

        void Quit( HWND hWnd, int iReturnValue );

        void togglecardchoice( HWND hCtlWnd, int cardno );

    public:

        std::vector<int> discard_cards;

        HINSTANCE hInst;

        MainWnd() {

            hInst = 0;

        }


        virtual ~MainWnd() {}

        void setcard( HWND hWnd, int iCtlID, int CardID );


        INT_PTR bUserDlgProc( HWND hDlg, UINT uiMsg, WPARAM wParam, LPARAM lParam ) override;

};


#endif /* __H_MAINWND_H__ */
