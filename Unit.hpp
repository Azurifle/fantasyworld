#ifndef UNIT
#define UNIT
#pragma once

namespace G6037599
{
  class Type_data;
  class Tile_data;

  class Unit
  {
  public:
    Unit(const char* t_name, const char* t_dead_message, const char* t_atk_name
      , int t_max_hp, int t_atk, int t_max_atk, char t_symbol, const COORD& t_pos);
    ~Unit() = default;
    Unit(const Unit& t_to_copy);
    Unit& operator=(const Unit& t_to_copy);
  private:
    std::shared_ptr<Type_data> m_type_ = nullptr;
    std::unique_ptr<Tile_data> m_tile_ = nullptr;
    int m_hp_ = 0;
  };
}

#endif //UNIT
