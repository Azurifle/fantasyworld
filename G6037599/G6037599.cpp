// G6037599.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Fantasy_world_2_d.hpp"//.cpp include .hpp & .hpp forward declare if not inheritance

namespace G6037599
{
  void back_to_main_menu()
    , memory_pool_v1()
    , fantasy_world()
    , fantasy_world_2_d()
    , hero_in_fantasy_world();

  //___ Main menu ____________________________________________________________________________
  int main_menu()
  {
    do
    {
      puts(" === Game Engine Projects =======================");
      puts("By: Darlyn Sirikasem G6037599");
      puts("");
      puts("");
      puts("         /////////////////////// Project list /////////////////////////////");
      puts("");
      puts("                    1. Memory Pool Manager v1.");
      puts("");
      puts("                    2. Fantasy World.");
      puts("");
      puts("                    3. Fantasy World 2D Grid + Code Refactor 1.");
      puts("");
      puts("                    4. A Hero in the Fantasy World.");
      puts("");
      puts("         //////////////////////////////////////////////////////////////////");
      puts("");
      puts("");
      const auto LAST_OPTION = 4;
      std::cout << "Input <1 - " << LAST_OPTION << "> or <0> to exit: ";
      auto choice = 0;
      do
      {
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        switch (choice)
        {
        case 1: system("CLS");
          memory_pool_v1();
          back_to_main_menu();
          break;
        case 2: system("CLS");
          fantasy_world();
          back_to_main_menu();
          break;
        case 3: system("CLS");
          fantasy_world_2_d();
          back_to_main_menu();
          break;
        case LAST_OPTION: system("CLS");
          hero_in_fantasy_world();
          back_to_main_menu();
          break;

        case 0: puts("");
          puts(" === End of program. =======================");
          fflush(stdin);
          getchar();
          return 0;
        default: puts("");
          std::cout << "Please input only <1 - " << LAST_OPTION << "> or <0> to exit: ";
        }
      } while (choice < 0 || choice > LAST_OPTION);
      system("CLS");
    } while (true);
  }
  
  void back_to_main_menu()
  {
    std::cout << std::endl
      << "Please <Any key> to main menu: ";
    getchar();
  }

  //___ Projects ____________________________________________________________________________
  void memory_pool_v1()
  {
    puts(" === Memory Pool Manager v1. =======================");
    puts("Work in progress.");
  }

  void fantasy_world()
  {
    puts(" === Fantasy World. =======================");
    const auto MONSTERS = 120, HERO_MAX_HP = 500;
    Fantasy_world_2_d world(MONSTERS);//Stack Overflow people suggest using stack over heap
    puts("");
    world.print_monster_list();
    puts("");
    world.create_player("NoOne the hero", HERO_MAX_HP);
    std::cout << std::endl << "Press <Any key> to update ";
    getchar();
    puts("");
    world.update();
  }

  void fantasy_world_2_d()
  {
    const auto TOPIC = " === Fantasy World 2D Grid. =======================";
    puts(TOPIC);
    const auto SIZE = 30, MONSTERS = 10;
    Fantasy_world_2_d world(SIZE, SIZE, MONSTERS);
    auto choice = 0;
    while (true)
    {
      world.print_grid();
      std::cout << std::endl
        << "Input <Any key> to update or <0> to exit: ";
      std::cin >> choice;
      std::cin.clear();
      std::cin.ignore(INT_MAX, '\n');
      switch (choice)
      {
      case 0: return;
      default: system("CLS");
      }
      world.update();
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