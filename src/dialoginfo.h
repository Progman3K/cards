#ifndef __H_DIALOGINFO_H__
#define __H_DIALOGINFO_H__


#include <vector>
#include "dbg_hlp.h"


typedef unsigned short UTF_16;


#if defined( __MINGW32__ ) || defined( _MSC_VER )

#define Endian16_Swap( s )           htons( s )
#define Endian32_Swap( l )           htonl( l )
#define Endian64_Swap( l )           htonll( l )

#else
#include <endian.h>
#endif



#if ! defined( __BYTE_ORDER )


#if __LITTLE_ENDIAN__ || defined( _M_IX86 ) || defined( _M_X64 )
#define I386PE_INT16_TO_HOST( s )    (s)
#define I386PE_INT32_TO_HOST( i )    (i)
#define I386PE_INT64_TO_HOST( l )    (l)
#else
#define I386PE_INT16_TO_HOST( s )    Endian16_Swap( s )
#define I386PE_INT32_TO_HOST( i )    Endian32_Swap( i )
#define I386PE_INT64_TO_HOST( l )    Endian64_Swap( l )
#endif


#else


# if __BYTE_ORDER == __LITTLE_ENDIAN
#define I386PE_INT16_TO_HOST( s )    (s)
#define I386PE_INT32_TO_HOST( i )    (i)
#define I386PE_INT64_TO_HOST( l )    (l)
#else
#define I386PE_INT16_TO_HOST( s )    __bswap_16( s )
#define I386PE_INT32_TO_HOST( i )    __bswap_32( i )
#define I386PE_INT64_TO_HOST( l )    __bswap_64( l )
#endif


#endif


typedef struct {

    uint16_t iCtlID;

    POINT    pt;

    unsigned cx;
    unsigned cy;

} ChildDimensions;


class DialogInfo {


        std::vector<ChildDimensions> child;


        void MoveChildren( HWND hDlg ) {

            for ( unsigned u = 0; u < child.size(); u++ ) {

                HWND hWnd = GetDlgItem( hDlg, child.at( u ).iCtlID );

                if ( NULL != hWnd ) {

                    MoveWindow( hWnd, (int)child.at( u ).pt.x, (int)child.at( u ).pt.y, (int)child.at( u ).cx, (int)child.at( u ).cy, false );

                } else {

                    TRACE( ID_DBG_MINUTIAE, "Dialog ID " << child.at( u ).iCtlID << " not found!" EOL );

                }

            }

        }


        const UTF_16 * skip_over( const UTF_16 * pszSource );


        void AdjustForFont( HWND hWnd, int x, int y, unsigned CX, unsigned CY, RECT & r ) {

            r.left   =          x;
            r.top    =          y;
            r.right  = r.left + CX;
            r.bottom = r.top  + CY;

            MapDialogRect( hWnd, &r );

        }


    public:


        unsigned cx;
        unsigned cy;


        DialogInfo() {

            cx = 0;
            cy = 0;

        }


        void MoveTo( HWND hWnd, int x, int y ) {

            MoveWindow( hWnd, x, y, cx, cy, false );

            MoveChildren( hWnd );

        }


        bool Record( HINSTANCE hInst, LPCTSTR lpszDlgID, HWND hWnd );

};


#endif /* __H_DIALOGINFO_H__ */
