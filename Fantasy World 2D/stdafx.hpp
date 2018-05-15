// stdafx.hpp : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.hpp"

#include <cstdio>
#include <tchar.h>



// TODO: reference additional headers your program requires here
#define CRTDBG_MAP_ALLOC

#include <iostream>
#include <vector>
#include <ctime>
#include <memory>
#include <conio.h>

#include <cassert>
#define REQUIRE(condition) assert(condition)//validate input
#define PROMISE(condition) assert(condition)//validate output