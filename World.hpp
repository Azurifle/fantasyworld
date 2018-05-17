#ifndef FANTASY_WORLD_2_D
#define FANTASY_WORLD_2_D
#pragma once

namespace G6037599
{
  class Unit;

	class World
	{
	public:
    static const int NOT_ASSIGN = -1;

		World() = default;
		explicit World(int t_monsters);
		World(int t_rows, int t_columns, int t_monsters);
		~World();

    void print_monster_list() const;

	  void update();
		void create_player(const char* t_name, int t_hp);
	  void create_player(const char* t_name, int t_hp, const char* t_weapon, int t_attack_power);
    void build_grid();
	  void respawn_monster(int t_id);
	  void player_move(int t_x, int t_y);
	  void set_restart();
	private:
		std::vector<std::unique_ptr<std::vector<std::weak_ptr<Unit> >> > m_grid_;
		std::vector<std::shared_ptr<Unit> > m_monsters_;
    //COORD m_grid_start_cursor_ = {0, 0};
		std::shared_ptr<Unit> m_player_ = nullptr;
	  bool m_is_restart_ = false;

	  enum Special_value { PLAYER_ID = -1, NONE, FIRST_INDEX = 0};
		int m_zombie_count_ = NONE, m_orc_count_ = NONE, m_doremon_count_ = NONE;

    bool has_unit_on(int t_x, int t_y);
    bool is_fighting_w_player(std::shared_ptr<Unit> unit) const;
    bool is_player_fighting() const;

		void add_random_monsters(int t_id);
    void spawn_player();
    void clear(int t_x, int t_y);
    void reset();
	};
}
#endif //FANTASY_WORLD_2_D