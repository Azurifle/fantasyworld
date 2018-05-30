#ifndef SPAWN_TO
#define SPAWN_TO
#pragma once
#include "Spawn_point.hpp"
#include "Map.hpp"

namespace G6037599
{
  template <class T>
  class Spawn_to : public Spawn_point
  {
  public:
    //LNK2019 error when put definition in .cpp
    Spawn_to<T>(const std::shared_ptr<Type_data> t_type
      , const std::shared_ptr<Console> t_m_console, const std::shared_ptr<Map> t_m_map)
    : Spawn_point(t_type, t_m_console, t_m_map) {}
    
    ~Spawn_to<T>() = default;

    Spawn_to<T>(const Spawn_to<T>& t_to_copy) : Spawn_point(t_to_copy) {
      copy_from(t_to_copy);
    }

    Spawn_to<T>& operator=(const Spawn_to<T>& t_to_copy) {
      copy_from(t_to_copy);
      return *this;
    }

    //___ public _____________________________________________
    int get_last_id() const override {
      REQUIRE(m_monsters_.size() > 0);
      return m_monsters_.back()->get_id();
    }

    int find_hp(const int t_id) const override {
      REQUIRE(m_monsters_.size() > 0);
      REQUIRE(t_id > Map::NO_UNIT);
      return m_monsters_[find_index(t_id)]->get_hp();
    }

    bool damaged_n_dies(const int t_monster_id, const int t_damage) const override {
      REQUIRE(m_monsters_.size() > 0);
      REQUIRE(t_monster_id > Map::NO_UNIT);

      const auto INDEX = find_index(t_monster_id);
      m_monsters_[INDEX]->damaged(t_damage);
      set_console_monster_hp(m_monsters_[INDEX]->get_hp(), get_type_max_hp());

      switch (m_monsters_[INDEX]->get_hp())
      {
      case 0: const auto NEW_POS = random_unoccupied_tile();
        map_move(m_monsters_[INDEX]->get_pos(), t_monster_id, NEW_POS);
        mark_console(m_monsters_[INDEX]->get_pos(), true);
        mark_console(NEW_POS);
        m_monsters_[INDEX]->set_pos(NEW_POS);
        m_monsters_[INDEX]->set_hp(get_type_max_hp());
        return true; default:;
      }
      return false;
    }

    void spawn(const int t_monsters) override {
      m_monsters_.clear();

      for (auto i = 0; i < t_monsters; ++i)
      {
        m_monsters_.push_back(std::make_unique<T>(share_type()));
        m_monsters_[i]->set_pos(random_unoccupied_tile());
        mark_map(m_monsters_[i]->get_pos(), m_monsters_[i]->get_id());
        mark_console(m_monsters_[i]->get_pos());
      }
    }

    void monsters_stronger(const int t_percent) const override {
      REQUIRE(t_percent > 0);

      auto hp_amount = static_cast<int>(round(get_type_max_hp() * t_percent / 100.0f));
      switch (hp_amount) { case 0: hp_amount = 1; default:; }

      increase_type_max_hp(hp_amount);

      for (auto it = m_monsters_.begin(); it != m_monsters_.end(); ++it)
      {
        (*it)->set_hp((*it)->get_hp() + hp_amount);
      }
    }

    COORD find_pos(const int t_monster_id) const override {
      REQUIRE(m_monsters_.size() > 0);
      REQUIRE(t_monster_id > Map::NO_UNIT);
      return m_monsters_[find_index(t_monster_id)]->get_pos();
    }

  private:
    std::vector<std::unique_ptr<T>> m_monsters_;

    void copy_from(const Spawn_to<T>& t_to_copy) {
      m_monsters_.clear();
      for (unsigned i = 0; i < t_to_copy.m_monsters_.size(); ++i)
      {
        m_monsters_.push_back(std::make_unique<T>(*t_to_copy.m_monsters_[i]));
      }
    }

    int find_index(const int t_monster_id) const {
      REQUIRE(m_monsters_.size() > 0);
      REQUIRE(t_monster_id > Map::NO_UNIT);

      for (unsigned i = 0; i < m_monsters_.size(); ++i)
      {
        if (m_monsters_[i]->get_id() == t_monster_id)
        {
          return i;
        }
      }
      PROMISE(false);//the monster is not managed by this spawner
      return Map::NO_UNIT;
    }
  };
}//G6037599

#endif //SPAWN_TO