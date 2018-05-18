#ifndef FANTASY_WORLD_2_D
#define FANTASY_WORLD_2_D
#pragma once

namespace G6037599
{
  class Unit;

	class World
	{
	public:
    enum Starting_value { NOT_ASSIGN = -1, NONE };

		World() = default;
		explicit World(int t_monsters);
		World(int t_rows, int t_columns, int t_monsters);
		~World();

    void print_monster_list() const;

	  void update()
      , create_player(const char* t_name, int t_hp)
      , create_player(const char* t_name, int t_hp, const char* t_weapon, int t_attack_power)
      , respawn_monster(int t_id)
      , build_console(), build_grid()
      , player_move(int t_x, int t_y)
      , set_restart();

	  void open_console() const;
    void end_console_line();
	private:
		std::vector<std::unique_ptr<std::vector<std::weak_ptr<Unit> >> > m_grid_;
		std::vector<std::shared_ptr<Unit> > m_monsters_;
	  COORD m_console_start_cursor_ = { NOT_ASSIGN, NOT_ASSIGN }
      , m_console_cursor_ = { NOT_ASSIGN, NOT_ASSIGN }
    , m_grid_start_cursor_ = { NOT_ASSIGN, NOT_ASSIGN };

	  enum Special_value
    {
      PLAYER_ID = -1, FIRST_INDEX, SPACE_BEFORE_CONSOLE = 2, SPACE_BETWEEN_GRID, CONSOLE_ROWS = 6
    };
		std::shared_ptr<Unit> m_player_ = nullptr;
		int m_zombie_count_ = NONE, m_orc_count_ = NONE, m_doremon_count_ = NONE;
    bool m_is_restart_ = false;

    bool has_unit_on(int t_x, int t_y) const
      , is_fighting_w_player(std::shared_ptr<Unit> t_unit) const
      , is_player_fighting() const, is_grid_built() const;

		void add_random_monsters(int t_id), spawn_player()
      , clear(int t_x, int t_y), reset();
	  void move_grid_cursor(int t_x, int t_y, bool t_challenger = false) const;
    void clean_console();
	};
}
#endif //FANTASY_WORLD_2_D