#ifndef PROJECT_H_INCLUDE
#define PROJECT_H_INCLUDE


#include "deck.h"


#include <array>
#include <vector>
#include <algorithm>
#include <sstream>

#include "dbg_hlp.h"

#ifdef _WIN32

#include "mainwnd.h"
#include "about.h"

HICON Win32AppInit( HINSTANCE hInst );

extern BOOL bContinue;


#endif /* _WIN32 */


#endif /* PROJECT_H_INCLUDE */
