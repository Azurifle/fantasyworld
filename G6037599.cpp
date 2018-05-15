// G6037599.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Fantasy_world_2_d.hpp"//.cpp include .hpp & .hpp forward declare if not inheritance
#include "Unit.hpp"

namespace G6037599
{
  char press_any_key();
  void back_to_main_menu()
    , fantasy_world()
    , fantasy_world_2_d()
    , hero_in_fantasy_world();

  //___ Main menu ____________________________________________________________________________
  int main_menu()
  {
    do
    {
      puts(" === Game Engine Fantasy World Projects =======================");
      puts("By: Darlyn Sirikasem G6037599");
      puts("");
      puts("");
      puts("         /////////////////////// Project list /////////////////////////////");
      puts("");
      puts("                    1. Fantasy World.");
      puts("");
      puts("                    2. Fantasy World 2D Grid + Code Refactor 1.");
      puts("");
      puts("                    3. A Hero in the Fantasy World.");
      puts("");
      puts("         //////////////////////////////////////////////////////////////////");
      puts("");
      puts("");
      const auto OPTION_1 = 1, OPTION_2 = 2, OPTION_3 = 3, OPTION_0 = 0;
      std::cout << "Input <" << OPTION_1 << " - " << OPTION_3 << "> or <" << OPTION_0 << "> to exit: ";
      auto choice = Unit::NOT_ASSIGN;
      do
      {
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        switch (choice)
        {
        case OPTION_1: system("CLS");
          fantasy_world();
          back_to_main_menu();
          break;
        case OPTION_2: system("CLS");
          fantasy_world_2_d();
          back_to_main_menu();
          break;
        case OPTION_3: system("CLS");
          hero_in_fantasy_world();
          back_to_main_menu();
          break;

        case OPTION_0: puts("");
          puts(" === End of program. =======================");
          press_any_key();
          return 0;
        default: puts("");
          std::cout << "Please input only <" << OPTION_1 << " - " << OPTION_3
            << "> or <" << OPTION_0 << "> to exit: ";
        }
      } while (choice < OPTION_0 || choice > OPTION_3);
      system("CLS");
    } while (true);
  }

  char press_any_key()
  {
    const char key = _getch();
    _getch();
    return key;
  }

  void back_to_main_menu()
  {
    std::cout << std::endl
      << "Input <Any key> to main menu: ";
    press_any_key();
  }

  //___ Projects ____________________________________________________________________________
  void fantasy_world()
  {
    puts(" === Fantasy World. =======================");
    const auto MONSTERS = 120, HERO_MAX_HP = 500;
    Fantasy_world_2_d world(MONSTERS);//Stack Overflow people suggest using stack over heap
    puts("");
    world.print_monster_list();
    puts("");
    world.create_player("NoOne the hero", HERO_MAX_HP);
    std::cout << std::endl << "Press <Any key> to update: ";
    press_any_key();
    puts("");
    world.update();
  }

  void fantasy_world_2_d()
  {
    const auto TOPIC = " === Fantasy World 2D Grid. =======================";
    puts(TOPIC);
    const auto SIZE = 30, MONSTERS = 10;
    Fantasy_world_2_d world(SIZE, SIZE, MONSTERS);
    while (true)
    {
      world.print_grid();
      std::cout << std::endl
        << "Press <Any key> to update or <0> to exit: ";
      switch ( press_any_key() )
      {
      case '0': return;
      default: break;
      }
      world.update();
      system("CLS");
      puts(TOPIC);
      std::cout << "World " << SIZE << "x" << SIZE << " grid with "
        << MONSTERS << " monsters spawn randomly." << std::endl;
    }
  }

  void hero_in_fantasy_world()
  {
    puts(" === A Hero in the Fantasy World. =======================");
    puts("Work in progress.");
  }
}//G6037599

int main()
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  return G6037599::main_menu();
}