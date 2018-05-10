// FantasyWorld2D.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fantasy_world_2_d.h"

int main()
{
	fantasy_world_2_d world(30, 30, 10);
	auto choice = -1;
	while (true)
	{
		world.update();
		world.print_grid();
		cout << endl
			<< "Input <1> to update or <0> to exit: ";
		cin >> choice;
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		switch (choice)
		{
		case 0: return 0;
		default: system("CLS");
		}
	}
}

