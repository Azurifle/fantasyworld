// G6037599.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Week_1/Animal.hpp"
#include "Week_7/Logger.hpp"
#include "Week_7/Stopwatch.hpp"

int main()
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  G6037599::oop_demo();
  //G6037599::logger_demo();
  //G6037599::Stopwatch::demo();

  puts("");
  puts("============================ End of Program ====================================");
  _getch();
  _getch();
}
