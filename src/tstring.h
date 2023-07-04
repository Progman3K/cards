

#ifndef __TSTRING_H__
#define __TSTRING_H__


#include <string>

//#include <tchar.h>
#if defined( UNICODE ) || defined( _UNICODE )
typedef wchar_t TCHAR;
#else
typedef char TCHAR;
#endif


class TSTRING : public std::basic_string<TCHAR> {

#if defined( _UNICODE ) || defined( UNICODE )

    basic_string<char> ascii;

#endif

    public:

        TSTRING & absorb( const char * psz ) {

            clear();

            for ( ; *psz; psz++ ) {

                append( 1, *psz );

            }

            return *this;

        }

        const char * asciiz() {

#if defined( _UNICODE ) || defined( UNICODE )

            ascii.clear();

            for ( unsigned u = 0; u < size(); u++ ) {

                ascii.append( 1, (char)at( u ) );

            }

            return ascii.c_str();

#else
            return c_str();
#endif

        }

#if 0
        void FromUTF8( const char * psz ) {

            int iRet =  MultiByteToWideChar( CP_UTF8, 0, psz, -1, nullptr, 0 );

            resize( iRet + 1 );

            MultiByteToWideChar( CP_UTF8, 0, psz, -1, (LPTSTR)c_str(), (int)size() );

        }

        const char * ToUTF8( void ) {

            int iRet =  WideCharToMultiByte( CP_UTF8, 0, c_str(), -1, nullptr, 0, nullptr, nullptr );

            ascii.resize( iRet + 1 );

            WideCharToMultiByte( CP_UTF8, 0, c_str(), -1, (LPSTR)ascii.c_str(), (int)ascii.size(), nullptr, nullptr );

            return ascii.c_str();

        }
#endif


#if 0
        unsigned LoadString( HINSTANCE hInst, UINT uiStringID ) {

            clear();

     /*
        This is disabled because the method of locating a string,
        obtaining its length, pre-allocating its length and then
        copying it directly to a TSTRING object doesn't seem to
        work very well.
        Refinement of the algorithm will be done later.
        For now, a double-copy of a restricted-maximum length 
        will have to do.
     */

            HRSRC hString = FindResource( hInst, MAKEINTRESOURCE( uiStringID / 16 ) + 1, RT_STRING );

            if ( 0 == hString ) {

                return 0;

            }

            HGLOBAL h = LoadResource( hInst, hString );

            if ( 0 == h ) {

                return 0;

            }

            LPCWSTR pwsz = (LPCWSTR)LockResource( h );

            if ( pwsz ) {

                // okay now walk the string table
                for ( unsigned i = 0; i < uiStringID & 15; i++ ) {

                    pwsz += 1 + (UINT)*pwsz;

                }

                UnlockResource( pwsz );

            }

            FreeResource( h );

            DWORD dwSize = SizeofResource( hInst, hString );

            if ( 0 == dwSize ) {

                return 0;

            }

            resize( ( dwSize / sizeof( TCHAR ) ) + sizeof( TCHAR ) );

            return ::LoadString( hInst, uiStringID, (TCHAR *)c_str(), ( dwSize / sizeof( TCHAR ) ) );
//#else

    TCHAR szString[4096];
    ZeroMemory( szString, sizeof( szString ) );

    ::LoadString( hInst, uiStringID, szString, ( sizeof( szString ) / sizeof( TCHAR ) ) - 1 );

    assign( szString );

    return (unsigned)size();


        }
#endif

};


#endif /* __TSTRING_H__ */
