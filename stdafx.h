// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: reference additional headers your program requires here
#define CRTDBG_MAP_ALLOC

#include <iostream>
#include <vector>
#include <memory>
#include <conio.h>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

//console cursor manipulation
#include <windows.h>
#include <winuser.h>
#include <processenv.h>
#include <consoleapi2.h>
#include <winbase.h>

#include <cassert>
#define REQUIRE(condition) assert(condition)//validate input
#define PROMISE(condition) assert(condition)//validate output