// FantasyWorld.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "fantasy_world.h"

int main()
{
	auto* world = new fantasy_world(120);
	world->create_player("Luka the hero", 500);
	world->update();
	delete world;
    return 0;
}

