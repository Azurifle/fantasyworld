// G6037599.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game_Engine/Game_engine.hpp"

int main()
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  G6037599::Game_engine::start();
}
