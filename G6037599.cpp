// G6037599.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Car_game.hpp"
//#include "Fantasy_Game/World.hpp"

int main()
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  Car_game().run();
}
