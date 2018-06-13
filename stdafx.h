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

#include <iostream>//std::cout
#include <iomanip>//std::width, fill
#include <conio.h>//_getch()
#include <string>
#include <fstream>//file stream
#include <sstream>//string tokenizer
#include <vector>
#include <memory>//smart ptr
#include <ctime>//clock()
#include <array>//bmp reading

//console cursor manipulation
#include <windows.h>
#include <winuser.h>
#include <processenv.h>
#include <consoleapi2.h>
#include <winbase.h>

#include <cassert>
#define REQUIRE(condition) assert(condition)//validate input
#define PROMISE(condition) assert(condition)//validate output