#ifndef WORLD
#define WORLD
#pragma once
#include "Map.hpp"

namespace G6037599
{
  class Console;
  class Unit;
  class Spawn_point;
  class Map;

	class World
	{
	public:
    static const char* MONSTER_CONF_PATH, * PLAYER_NAME;
	  static const COORD UP, DOWN, LEFT, RIGHT, ZERO;
    const enum Enum 
	  { 
	    PLAYER_MAX_HP = 50, PLAYER_ATK = 20, PLAYER_MAX_ATK = 22, MONSTERS = 101
	  };

    static short limit_interval(int t_number, int t_min, int t_max);

	  World();
	  ~World() = default;
    World(const World& t_to_copy);
    World& operator=(const World& t_to_copy);

	  void player_move(COORD t_move);
	  void move_cursor(COORD t_move);
	  void update();
	  void exit() const;
	private:
    std::vector<std::unique_ptr<Spawn_point>> m_spawners_;
    std::shared_ptr<Map> m_map_ = nullptr;
    std::unique_ptr<Console> m_console_ = nullptr;
    std::unique_ptr<Unit> m_player_ = nullptr;

    char tokenize(const std::string& t_line, std::string& t_name
      , std::string& t_dead_message, std::string& t_atk_name
      , int& t_max_hp, int& t_atk, int& t_max_atk) const;
    void read_monster_types();
    void spawners_spawn_monster();
    void copy_from(const World& t_to_copy);
    void monster_stronger();
	};

  const char* World::MONSTER_CONF_PATH = "monster_conf.txt";
  const char* World::PLAYER_NAME = "NoOne The Hero";
  const COORD World::UP = { 0, -1 };
  const COORD World::DOWN = { 0, 1 };
  const COORD World::LEFT = { -1, 0 };
  const COORD World::RIGHT = { 1, 0 };
  const COORD World::ZERO = { 0, 0 };
}
#endif //WORLD