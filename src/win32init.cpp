

#include "project.h"


void Cleanup( void ) {


}



static BOOL bRegisterClasses( HINSTANCE hInst, HICON hClassIcon ) {

    TRACE( ID_DBG_MINUTIAE, EOL "Initializing instance " << hInst << EOL );

    WNDCLASS wc;

    ZeroMemory( &wc, sizeof( wc ) );

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = DefDlgProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = DLGWINDOWEXTRA;
    wc.hInstance     = hInst;
    wc.hIcon         = hClassIcon;

#ifdef _WIN32_WCE
    wc.hCursor       = NULL;
#else
    wc.hCursor       = LoadCursor( NULL, IDC_ARROW );
#endif /* _WIN32_WCE */

//    TCHAR szClassName[] = TEXT( IDSZ_MAIN_WINDOW_CLASS );

    wc.hbrBackground = NULL;
    wc.lpszMenuName  = NULL;
//    wc.lpszClassName = IDSZ_MAIN_WINDOW_CLASS;
    wc.lpszClassName = _T( IDSZ_MAIN_WINDOW_CLASS );

    if ( 0 == RegisterClass( &wc ) ) {

        MessageBox( HWND_DESKTOP, TEXT( "REGISTERING MAIN WINDOW CLASS FAILED" ), PROGRAM_FATAL_ERROR, MB_OK | MB_ICONERROR );
        return false;

    }

    return true;

}


HICON Init( HINSTANCE hInst ) {

    INITCOMMONCONTROLSEX InitCtrlEx;

    InitCtrlEx.dwSize = sizeof( INITCOMMONCONTROLSEX );
    InitCtrlEx.dwICC  = ICC_PROGRESS_CLASS;

    InitCommonControlsEx( &InitCtrlEx );

    HICON   hMainIcon;

    if ( NULL == ( hMainIcon = LoadIcon( hInst, MAKEINTRESOURCE( IDI_MAIN ) ) ) ) {

        TRACE( ID_DBG_ERROR, "Load main icon failed" EOL );
        MessageBox( HWND_DESKTOP, TEXT( "LOAD MAIN ICON FAILED - RESOURCES MISSING" ), PROGRAM_FATAL_ERROR, MB_OK | MB_ICONERROR );
        return NULL;

    }

    if ( ! bRegisterClasses( hInst, hMainIcon ) ) {

        DestroyIcon( hMainIcon );
        TRACE( ID_DBG_ERROR, "Register classes failed" EOL );
        return NULL;

    }

    return hMainIcon;

}
