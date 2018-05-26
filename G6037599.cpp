// G6037599.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "World.hpp"

int wait_key(int t_miliseconds);

int main()
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  G6037599::World world;

  enum Wait_key
  {
    HALF_SECOND = 500, ESC = 27, ARROW = -32,
    ARROW_UP = 72, ARROW_DOWN = 80, ARROW_LEFT = 75, ARROW_RIGHT = 77
  };
  while(true)
  {
    switch (wait_key(HALF_SECOND))
    {
      case 'w': _getch();
        world.player_move(world.UP);
        break;
      case 's': _getch();
        world.player_move(world.DOWN);
        break;
      case 'a': _getch();
        world.player_move(world.LEFT);
        break;
      case 'd': _getch();
        world.player_move(world.RIGHT);
        break;
      case ARROW: switch(_getch())
        {
          case ARROW_UP: world.move_cursor(world.UP); break;
          case ARROW_DOWN: world.move_cursor(world.DOWN); break;
          case ARROW_LEFT: world.move_cursor(world.LEFT); break;
          case ARROW_RIGHT: world.move_cursor(world.RIGHT); break; 
          default: world.update();
        } break;
      case ESC: _getch();
        world.exit();
      return 0; 
      default: _getch();
         world.update();
    }
  }//game loop
}

int wait_key(const int t_miliseconds)
{
  Sleep(t_miliseconds);

  const auto NO_KEY_PRESS = 0;
  switch (_kbhit())
  {
  case NO_KEY_PRESS: return NO_KEY_PRESS;
  default: return _getch();
  }
}