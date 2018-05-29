#ifndef SPAWN_TO
#define SPAWN_TO
#pragma once
#include "Spawn_point.hpp"

namespace G6037599
{
  template <class T>
  class Spawn_to : public Spawn_point
  {
  public:
    Spawn_to<T>(std::shared_ptr<Type_data> t_type
      , std::shared_ptr<Console> t_m_console, std::shared_ptr<Map> t_m_map);
    ~Spawn_to<T>() = default;
    Spawn_to<T>(const Spawn_to<T>& t_to_copy);
    Spawn_to<T>& operator=(const Spawn_to<T>& t_to_copy);

    int get_last_id() const override;
    int find_hp(int t_id) const override;
    bool damaged_n_dies(int t_monster_id, int t_damage) const override;
    void spawn(int t_monsters) override;
    void monsters_stronger(int t_percent) const override;
    COORD find_pos(int t_monster_id) const override;
  private:
    std::vector<std::unique_ptr<T>> m_monsters_;

    void copy_from(const Spawn_to<T>& t_to_copy);
    int find_index(int t_monster_id) const;
  };
}//G6037599

#endif //SPAWN_TO