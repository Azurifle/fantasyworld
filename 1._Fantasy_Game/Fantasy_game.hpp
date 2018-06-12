#ifndef G6037599_FANTASY_GAME_HPP
#define G6037599_FANTASY_GAME_HPP
#pragma once
#include "Unit.hpp"
#include "Spawn_point.hpp"

namespace G6037599
{
  class Console;
  class Map;
  class Type_data;

	class Fantasy_game final
	{
	public:
    static const char* MONSTER_CONF_PATH, * PLAYER_NAME;
	  static const COORD UP, DOWN, LEFT, RIGHT, ZERO;
    const enum Enum 
	  { 
      NO_KEY_PRESS, PLAYER_MAX_HP = 50
	    , PLAYER_ATK = 20, PLAYER_MAX_ATK = 22
	  };

    static void run();
    static short limit_interval(int t_number, int t_min, int t_max);
    static int wait_key(int t_miliseconds);
	  
	  Fantasy_game();
    ~Fantasy_game() = default;

    void player_move();
	  void player_move(COORD t_move);
	  void move_cursor(const COORD& t_move);
	  void update();
	  void exit() const;
	private:
    std::vector<std::unique_ptr<Spawn_point>> m_spawners_;
    std::shared_ptr<Map> m_map_{};
    std::shared_ptr<Console> m_console_{};
    COORD m_player_cursor_pos_{};
    std::unique_ptr<Unit> m_player_{};
    int m_monster_count_, m_level_monsters_;

    Fantasy_game(const Fantasy_game& t_to_copy) = default;
    Fantasy_game(Fantasy_game&& t_to_move) = default;
    Fantasy_game& operator=(const Fantasy_game& t_to_copy) = default;
    Fantasy_game& operator=(Fantasy_game&& t_to_move) noexcept = default;

    std::shared_ptr<Type_data> tokenize(const std::string& t_line) const;
    void read_monster_types();
    void spawn_spawners();
    void spawners_spawn_monster();
    void monsters_stronger();
    void game_reset();
	  void check_battle();
	  int find_spawner_index(int t_monster_id) const;
    void update_monster_status_hp() const;
    void update_cursor_status_hp() const;
    void player_move_into_battle();
    void monster_dies(int t_index);
    void next_stage();
	};
}//G6037599

#endif //G6037599_FANTASY_GAME_HPP