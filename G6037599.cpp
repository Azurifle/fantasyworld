// G6037599.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Logger.hpp"
//#include "Stopwatch.hpp"

int main()
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  //G6037599::Stopwatch::demo();
  G6037599::logger_demo();

  puts("");
  puts("============================ End of Program ====================================");
  _getch();
  _getch();
}
