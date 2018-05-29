#ifndef MAP
#define MAP
#pragma once

namespace G6037599
{
  class Map
  {
  public:
    const enum Enum 
    { 
      NO_UNIT = -1, SIZE = 30, MIDDLE = SIZE / 2
    };
    struct Tile { int owner_id = NO_UNIT, attacker_id = NO_UNIT; };

    Map();
    ~Map() = default;
    Map(const Map& t_to_copy);
    Map& operator=(const Map& t_to_copy);

    void marked(const COORD& t_pos, int t_id);
    bool is_attacker(const COORD& t_pos, int t_id) const;
    void move(const COORD& t_from, int t_id, const COORD& t_to);
    int get(const COORD& t_pos) const;
    COORD random_unoccupied() const;
    void reset();
  private:
    std::vector<std::unique_ptr< std::vector<Tile> >> m_grid_;

    void copy_from(const Map& t_to_copy);
  };
}//G6037599

#endif //MAP