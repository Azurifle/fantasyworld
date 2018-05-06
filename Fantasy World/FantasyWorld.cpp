// FantasyWorld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fantasy_world.h"

int main()
{
	puts("=== Fantasy World =======================");
	fantasy_world world(120);//Stack Overflow people suggest using stack over heap
	puts("world created.\n");
	world.print_monster_list();
	world.create_player("NoOne the hero", 500);
	puts("NoOne the hero has loged in.");
	cout << endl << "press any key to update ";
	_getch();
	cout << endl;
	world.update();
	_getch();
    return 0;
}

