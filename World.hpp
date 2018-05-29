#ifndef WORLD
#define WORLD
#pragma once

namespace G6037599
{
  class Console;
  class Unit;
  class Spawn_point;
  class Map;
  class Type_data;

	class World
	{
	public:
    static const char* MONSTER_CONF_PATH, * PLAYER_NAME;
	  static const COORD UP, DOWN, LEFT, RIGHT, ZERO;
    const enum Enum 
	  { 
      NO_KEY_PRESS, MONSTERS = 101
	    , PLAYER_MAX_HP = 50, PLAYER_ATK = 20, PLAYER_MAX_ATK = 22
	  };

    static short limit_interval(int t_number, int t_min, int t_max);
    static int wait_key(int t_miliseconds);
	  
	  World();
	  ~World() = default;
    World(const World& t_to_copy);
    World& operator=(const World& t_to_copy);

	  void player_move(COORD t_move = ZERO);
	  void move_cursor(const COORD& t_move);
	  void update();
	  void exit() const;
	private:
    std::vector<std::unique_ptr<Spawn_point>> m_spawners_;
    std::shared_ptr<Map> m_map_ = nullptr;
    std::shared_ptr<Console> m_console_ = nullptr;
    COORD m_player_cursor_pos_ = { 0, 0 };
    std::unique_ptr<Unit> m_player_ = nullptr;

    void copy_from(const World& t_to_copy);
    std::shared_ptr<Type_data> tokenize(const std::string& t_line) const;
    void read_monster_types();
    void spawners_spawn_monster();
    void monsters_stronger();
    void game_reset();
    void check_battle();
    void spawn_spawners();
	  int find_spawner_index(int t_monster_id) const;
    void update_monster_status_hp() const;
    void update_cursor_status_hp() const;
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