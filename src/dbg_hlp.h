#ifndef DBG_DEFINES_H
#define DBG_DEFINES_H


#include <cstring> // for strrchr
#include <cstdarg> // for varargs
#include <iostream> // for cout


#include <cassert> // for AddTimeStamp class
#include <iomanip> // for std::tm and std::get_time


#ifndef EOL
#define EOL "\n"
#endif


inline const char * f_name2( const char * path ) {

    const char * pszRet = path;

    const char * lastslashpos = strrchr( path, '/' );

    return lastslashpos ? lastslashpos + 1 : pszRet;

}


extern unsigned int gDebugging;


/* The debug channels */
#define ID_DBG_ERROR                    0b000000000001
#define ID_DBG_SEE_COMPUTER_HAND        0b000000000010
#define ID_DBG_USER_MESSAGES            0b000000000100
#define ID_DBG_MINUTIAE                 0b000000001000
#define ID_DBG_CHECKPOINT               0b000000010000
#define ID_DBG_UNUSED1                  0b000000100000
#define ID_DBG_UNUSED2                  0b000001000000
#define ID_DBG_UNUSED3                  0b000010000000
#define ID_DBG_UNUSED4                  0b000100000000
#define ID_DBG_UNUSED5                  0b001000000000
#define ID_DBG_UNUSED6                  0b010000000000
#define ID_DBG_UNUSED7                  0b100000000000


#define ID_DBG_MINIMUM                  ( ID_DBG_ERROR | ID_DBG_CHECKPOINT )


/* Which information channels should also include the source file name and line number */
#define ID_DBG_EXTRA_INFO               ( ID_DBG_ERROR | ID_DBG_CHECKPOINT | ID_DBG_MINUTIAE )

#if defined( UNICODE ) || defined( _UNICODE )
#define OP_TEXT std::wcout
typedef wchar_t TCHAR;
#else
#define OP_TEXT std::cout
typedef char TCHAR;
#endif

#define TRACE( levels, ... ) if ( ( levels & gDebugging ) || ( levels & ID_DBG_ERROR ) ) { if ( levels & ID_DBG_EXTRA_INFO ) { OP_TEXT << f_name2( __FILE__ ) << " line " << __LINE__ << " : " << __VA_ARGS__ ; } else { OP_TEXT << __VA_ARGS__ ; } } ; OP_TEXT.clear();


#endif /* DBG_DEFINES_H */
