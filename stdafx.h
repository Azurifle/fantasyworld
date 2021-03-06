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

#include <vector>
#include <chrono>//time in nanosec
#include <memory>//smart_ptr
#include <conio.h>//_getch()
#include <iostream>//cout
#include <string>
#include <iomanip>//std::setprecision(2)
#include <sstream>//std::stringstream
#include <GLFW/glfw3.h>

#include <windows.h>
#include <consoleapi.h>//ENABLE_QUICK_EDIT_MODE
#include <winbase.h>//GetStdHandle

#include <cassert>
#define REQUIRE(condition) assert(condition)//validate input
#define PROMISE(condition) assert(condition)//validate output