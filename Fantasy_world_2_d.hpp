#ifndef FANTASY_WORLD_2_D
#define FANTASY_WORLD_2_D
#pragma once

namespace G6037599
{
  class Unit;
  class Monster;

	class Fantasy_world_2_d
	{
	public:
		Fantasy_world_2_d() = default;
		explicit Fantasy_world_2_d(int t_monsters);
		Fantasy_world_2_d(int t_rows, int t_columns, int t_monsters);
		~Fantasy_world_2_d();

    void print_monster_list() const;
    void print_grid() const;

		void update();
		void create_player(const char* t_name, int t_hp);
	  void create_player(const char* t_name, int t_hp, const char* t_weapon, int t_attack_power);
		void spawn(int t_id);
		void despawn(int t_x, int t_y);
    void spawn_player();
	private:
		std::vector<std::unique_ptr<std::vector<std::weak_ptr<Unit> >> > m_grid_;
		std::vector<std::shared_ptr<Unit> > m_monsters_;
		std::shared_ptr<Unit> m_player_ = nullptr;
    enum Zero { NONE, FIRST_INDEX = 0 };
		int m_zombie_count_ = NONE, m_orc_count_ = NONE, m_doremon_count_ = NONE;

		void add_random_monsters(int t_id);
	};
}
#endif //FANTASY_WORLD_2_D