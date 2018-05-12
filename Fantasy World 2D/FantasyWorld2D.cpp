// FantasyWorld2D.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void assignment1_memory_pool_v1()
{
	puts(" === Assignment 1: Memory Pool Manager v1. =======================");
}

#include "fantasy_world_2_d.h"
void class_act1_fantasy_world()
{
	puts(" === Class Activities 1: Fantasy World. =======================");
	//fantasy_world_2_d world(120);//Stack Overflow people suggest using stack over heap
	puts("world created.\n");
	//world.print_monster_list();
	puts("");
	//world.create_player("NoOne the hero", 500);
	puts("NoOne the hero has loged in.");
	cout << endl << "Press <Any key> to update ";
	_getch();
	cout << endl;
	//world.update();
}

void assignment2_fantasy_world()
{
	puts(" === Assignment 2: Fantasy World 2D. =======================");
	auto world = make_unique<fantasy_world_2_d>(30, 30, 10);
	puts("World 30x30 grid created with 10 monsters spawn randomly.");
	puts("<id><type>:<HP>. z = Zombie (HP 2-3), o = Orc (HP 5-6), d = Doramon (HP 8-9).");

	auto choice = -1;
	while (true)
	{
		puts("");
		world->update();
		puts("");
		world->print_grid();
		cout << endl
			<< "Input <Any key> to update or <0> to exit: ";
		cin >> choice;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		switch (choice)
		{
		case 0: return;
		default: system("CLS");
		}
		puts(" === Assignment 2: Fantasy World 2D. =======================");
		puts("World 30x30 grid with 10 monsters spawn randomly.");
		puts("<id><type>:<HP>. z = Zombie (HP 2-3), o = Orc (HP 5-6), d = Doramon (HP 8-9).");
	}
}

void class_act2_hero_in_fantasy_world()
{
	puts(" === Class Activity 2: A Hero in the Fantasy World. =======================");

}

void back_to_main_menu()
{
	cout << endl
		<< "Please <Any key> to main menu: ";
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
		puts("1. Assignment 1: Memory Pool Manager v1.");
		puts("2. Class Activities 1: Fantasy World.");
		puts("3. Assignment 2: Fantasy World 2D.");
		puts("");
		cout << "Input <1 - 3> or <0> to exit: ";
		auto choice = -1;
		while (choice < 0 || choice > 3)
		{
			cin >> choice;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
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
			case 4: system("CLS");
				class_act2_hero_in_fantasy_world();
				back_to_main_menu();
				break;

			case 0: puts("");
				puts(" === End of program. =======================");
				fflush(stdin);
				_getch();
				return 0;
			default: cout << endl
				<< "Please input only <1 - 3> or <0> to exit: ";
			}
		}//while wrong choice
		system("CLS");
	}//while true
}

