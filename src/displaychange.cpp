

#include "project.h"


void MainWnd::OnDisplayChange( HWND hWnd, UINT /* uiBPP */, UINT cx, UINT cy ) {

    RECT r;

    GetWindowRect( hWnd, &r );

    if ( cy > cx ) {

        /* Portrait */
        portrait.MoveTo( hWnd, (unsigned long)r.left, (unsigned long)r.top );

    } else {

        /* Landscape */
        landscape.MoveTo( hWnd, (unsigned long)r.left, (unsigned long)r.top );

    }

    InvalidateRect( hWnd, 0, true );

}


const UTF_16 * DialogInfo::skip_over( const UTF_16 * p ) {

    unsigned u = 0;

    for ( u = 0;; u++ ) {

        if ( 0 == *p ) {

            break;

        }

        p++;

    }

    /* Point past the NUL */
    p++;

    if ( 0 != u % 2 ) {

        p++;

    }

    return p;

}


bool DialogInfo::Record( HINSTANCE hInst, LPCTSTR lpszDlgID, HWND hWnd ) {

    HRSRC hRes = FindResource( hInst, lpszDlgID, RT_DIALOG );

    if ( (HRSRC)0 == hRes ) {

        return false;

    }

    HGLOBAL hData = LoadResource( hInst, hRes );

    if ( (HGLOBAL)0 == hData ) {

        return false;

    }

    DLGTEMPLATE * pDlgHeader = (DLGTEMPLATE *)LockResource( hData );

    if ( 0 == pDlgHeader ) {

        FreeResource( hData );
        return false;

    }

    RECT r;

    TRACE( ID_DBG_MINUTIAE, "Recorded parent " << LOWORD( reinterpret_cast<uintptr_t>( lpszDlgID ) ) << ": (" << pDlgHeader->x << "," << pDlgHeader->y << "," << pDlgHeader->cx << "," << pDlgHeader->cy << ") - " << pDlgHeader->cdit << " children" EOL );

    AdjustForFont( hWnd, I386PE_INT16_TO_HOST( pDlgHeader->x ), I386PE_INT16_TO_HOST( pDlgHeader->y ), I386PE_INT16_TO_HOST( pDlgHeader->cx ), I386PE_INT16_TO_HOST( pDlgHeader->cy ), r );

    cx = (unsigned long)( r.right - r.left );
    cy = (unsigned long)( r.bottom - r.top );

    /* Add non-client area dimensions */
    cy += GetSystemMetrics( SM_CYCAPTION );
    cy += GetSystemMetrics( SM_CYMENUSIZE );
    cy += ( GetSystemMetrics( SM_CYDLGFRAME ) * 2 );
    cy += ( GetSystemMetrics( SM_CYBORDER ) * 2 );

    cx += ( GetSystemMetrics( SM_CXDLGFRAME ) * 2 );
    cx += ( GetSystemMetrics( SM_CXBORDER ) * 2 );

    child.clear();

    if ( 0 == I386PE_INT16_TO_HOST( pDlgHeader->cdit ) ) {

        FreeResource( hData );
        return true;

    }

    /* Access first 16-bit word immediately following the dialog header */
    const unsigned short * p = (const UTF_16 *)&pDlgHeader->cy;
    p++;

    // Is there a MenuName
    switch ( *p ) {

        case 0:

            // There is no menu
            p++;
            break;

        case 0xFFFF:

            // The following short is the menu resource ID
            p++;

//            DBGTRACE( "Dialog numerical menu ID %u", *p );

            p++;
            break;

        default:

            // What follows is an alphanumeric string of the resource ID.
            p = skip_over( p );
            break;

    }

    // Is there a class name
    switch ( *p ) {

        case 0:

            // There is no class string
            p++;
            break;

        case 0xFFFF:

            // The following short is the window-class ID
            p++;

//            DBGTRACE( "Dialog numerical menu ID %u", *p );

            p++;
            break;

        default:

            // What follows is an alphanumeric string of the class ID.
            p = skip_over( p );
            break;

    }

    // Jump over caption
    p = skip_over( p );

    // Jump over font
    p = skip_over( p );

    DLGITEMTEMPLATE * pControlData = (DLGITEMTEMPLATE *)p;


    for ( WORD u = 0; u < I386PE_INT16_TO_HOST( pDlgHeader->cdit ); u++ ) {

//        DBGTRACE( "Detected child %d: (%d,%d,%u,%u)", pControlData->id, pControlData->x, pControlData->y, pControlData->cx, pControlData->cy );

        AdjustForFont( hWnd, I386PE_INT16_TO_HOST( pControlData->x  ), I386PE_INT16_TO_HOST( pControlData->y  ), I386PE_INT16_TO_HOST( pControlData->cx ), I386PE_INT16_TO_HOST( pControlData->cy ), r );

        ChildDimensions cd;

        cd.pt.x   = r.left;
        cd.pt.y   = r.top;
        cd.cx     = (unsigned long)( r.right - r.left );
        cd.cy     = (unsigned long)( r.bottom - r.top );

        cd.iCtlID = I386PE_INT16_TO_HOST( pControlData->id );

        child.push_back( cd );

        uintptr_t ulOffset;

        p = (const UTF_16 *)&pControlData->id;

        p++;

        /* Control classname */
        switch( *p ) {

            case 0xFFFF:

                /* What follows is a numerical class-ID */
                p++;

                p++;
                break;

            default:

                /* What follows is an alphanumeric string of the class ID. */
                p = skip_over( p );

                break;

        }

        switch( *p ) {

            case 0xFFFF:

                /* Unidentified */
                /* What follows is a numerical class-ID */
                p++;

                p++;
                break;

            default:

                // Jump over Text
                p = skip_over( p );

                break;

        }

        // Increment over nExtraStuff
        p++;

//        DBGTRACE( "Calculate address: %p. Modulo remainder: by two %u, by four %u, by 8 %u", p, reinterpret_cast<uintptr_t>( p ) % 2, reinterpret_cast<uintptr_t>( p ) % 4, reinterpret_cast<uintptr_t>( p ) % 8 );
        ulOffset = reinterpret_cast<uintptr_t>( p ) % (uintptr_t)( sizeof( void * ) );

        if ( 0 != ulOffset ) {

              p = reinterpret_cast<const unsigned short *>(reinterpret_cast<uintptr_t>( p ) + ulOffset );

        }

        pControlData = (DLGITEMTEMPLATE *)p;

    }

    FreeResource( hData );

//    DBGTRACE( "Recorded %u child-controls", child.size() );

    return true;

}
