#ifndef UNIT
#define UNIT
#pragma once
#include "Tile_data.hpp"

namespace G6037599
{
  class Type_data;

  class Unit
  {
  public:
    explicit Unit(std::shared_ptr<Type_data> t_type);
    ~Unit() = default;
    Unit(const Unit& t_to_copy);
    Unit& operator=(const Unit& t_to_copy);

    COORD get_pos() const;
    int get_id() const;
    char get_symbol() const;
    int get_hp() const;

    void set_pos(const COORD& t_pos) const;    
    void damaged(int t_damage);
    void set_hp(int t_hp);
    int random_atk() const;
  private:
    std::shared_ptr<Type_data> m_type_ = nullptr;
    std::unique_ptr<Tile_data> m_tile_ = nullptr;
    int m_hp_ = 0;

    void copy_from(const Unit& t_to_copy);
  };
}

#endif //UNIT
