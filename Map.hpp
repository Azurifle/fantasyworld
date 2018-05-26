#ifndef MAP
#define MAP
#pragma once

namespace G6037599
{
  static const int NO_UNIT = -1;
  struct Tile { int owner_id = NO_UNIT, attacker_id = NO_UNIT; };

  class Map
  {
  public:
    const enum Enum { SIZE = 30 };

    Map();
    ~Map() = default;
    Map(const Map& t_to_copy);
    Map& operator=(const Map& t_to_copy);

    void marked(const COORD& t_pos, int t_id);
  private:
    std::vector<std::unique_ptr< std::vector<Tile> >> m_grid_;

    void copy_from(const Map& t_to_copy);
  };
}//G6037599

#endif //MAP