// FantasyWorld2D.cpp : Defines the entry point for the console application.
//

#include "stdafx.hpp"
#include "Fantasy_world_2_d.hpp"//.cpp include .hpp & .hpp forward declare

namespace G6037599
{
	void assignment1_memory_pool_v1()
	{
		puts(" === Assignment 1: Memory Pool Manager v1. =======================");
		puts("Work in progress.");
	}

	void class_act1_fantasy_world()
	{
		puts(" === Class Activities 1: Fantasy World. =======================");
    const auto MONSTERS = 120, HERO_MAX_HP = 500;
		Fantasy_world_2_d world(MONSTERS);//Stack Overflow people suggest using stack over heap
		puts("");
		world.print_monster_list();
		puts("");
		world.create_player("NoOne the hero", HERO_MAX_HP);
		std::cout << std::endl << "Press <Any key> to update ";
		_getch();
    puts("");
		world.update();
	}

	void assignment2_fantasy_world()
	{
		puts(" === Assignment 2: Fantasy World 2D. =======================");
    const auto SIZE = 30, MONSTERS = 10;
		Fantasy_world_2_d world(SIZE, SIZE, MONSTERS);
		auto choice = -1;
		while (true)
		{		
			world.update();
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
			puts(" === Assignment 2: Fantasy World 2D. =======================");
      std::cout << "World " << SIZE << "x" << SIZE << " grid with " 
		    << MONSTERS << " monsters spawn randomly." << std::endl;
		}
	}

	void class_act2_hero_in_fantasy_world()
	{
		puts(" === Class Activity 3: A Hero in the Fantasy World. =======================");
		puts("Work in progress.");
	}

	//___ Main menu ____________________________________________________________________________
	void back_to_main_menu()
	{
		std::cout << std::endl
			<< "Please <Any key> to main menu: ";
		fflush(stdin);
		_getch();
	}

	int main()
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		while (true)
		{
			puts(" === Game Engine Projects =======================");
			puts("By: Darlyn Sirikasem G6037599");
			puts("");
			puts(" --- Project list");
			puts("");
			puts("1. Assignment 1       : Memory Pool Manager v1.");
			puts("");
			puts("2. Class Activities 1 : Fantasy World.");
			puts("");
			puts("3. Assignment 2       : Fantasy World 2D Grid & Code Refactor 1.");
			puts("");
			puts("4. Class Activity 2   : A Hero in the Fantasy World.");
			puts("");
      const auto LAST_OPTION = 4;
			std::cout << "Input <1 - "<< LAST_OPTION <<"> or <0> to exit: ";
			auto choice = 0;
			while (choice < 0 || choice > LAST_OPTION)
			{
				std::cin >> choice;
				std::cin.clear();
				std::cin.ignore(INT_MAX, '\n');
				switch (choice)
				{
				case 1: system("CLS");
					assignment1_memory_pool_v1();
					back_to_main_menu();
					break;
				case 2: system("CLS");
					class_act1_fantasy_world();
					back_to_main_menu();
					break;
				case 3: system("CLS");
					assignment2_fantasy_world();
					back_to_main_menu();
					break;
				case LAST_OPTION: system("CLS");
					class_act2_hero_in_fantasy_world();
					back_to_main_menu();
					break;

				case 0: puts("");
					puts(" === End of program. =======================");
					fflush(stdin);
					_getch();
					return 0;
				default: puts("");
					std::cout << "Please input only <1 - "<< LAST_OPTION <<"> or <0> to exit: ";
				}
			}//while wrong choice
			system("CLS");
		}//while true
	}

}//namespace G6037599