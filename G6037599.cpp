// G6037599.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Fantasy_world_2_d.hpp"//.cpp include .hpp & .hpp forward declare if not inheritance

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
      const enum Option
      {
        NOT_ASSIGN = -1, OPTION_0_EXIT, OPTION_1, OPTION_2, OPTION_3
      };
      std::cout << "Input <" << OPTION_1 << " - " << OPTION_3 << "> or <" << OPTION_0_EXIT << "> to exit: ";
      int choice = NOT_ASSIGN;
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

        case OPTION_0_EXIT: puts("");
          puts(" === End of program. =======================");
          press_any_key();
          return OPTION_0_EXIT;
        default: puts("");
          std::cout << "Please input only <" << OPTION_1 << " - " << OPTION_3
            << "> or <" << OPTION_0_EXIT << "> to exit: ";
        }
      } while (choice < OPTION_0_EXIT || choice > OPTION_3);
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
      case '0': puts("");
        return;
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
    const auto TOPIC = " === A Hero in the Fantasy World. =======================";
    puts(TOPIC);
    const auto SIZE = 30, MONSTERS = 10, HERO_MAX_HP = 500, HERO_ATTACK_DAMAGE = 1;
    Fantasy_world_2_d world(SIZE, SIZE, MONSTERS);
    world.create_player("NoOne the hero", HERO_MAX_HP, "Fist !", HERO_ATTACK_DAMAGE);
    //1 Hero be on map with monsters.
    //1 Monster no longer damaged every frame.
    while (true)
    {
      world.print_grid();
      std::cout << std::endl
        << "Press <W/S/A/D>: Move, <Other key>: Attack same tile, or <0>: Exit.";
      switch (press_any_key())
      {
      case 'w': break;//4 Hero can walk W/S/A/D 1 tile.
      case 's': break;
      case 'a': break;
      case 'd': break;
      case '0': puts("");
        return;
      default: break;//2 If Hero & monster on same tile they will attack each other each frame.
      }
      system("CLS");
      puts(TOPIC);
      world.update();//3 When hero die game reset. + print game status
    }
  }
}//G6037599

int main()
{
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  return G6037599::main_menu();
}