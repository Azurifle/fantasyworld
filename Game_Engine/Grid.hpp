#ifndef G6037599_GRID_HPP
#define G6037599_GRID_HPP
#pragma once

namespace G6037599
{
  class Grid final
  {
  public:
    Grid(const COORD& t_coord, int t_grid_cols, int t_grid_rows);
    ~Grid() = default;
  private:
    struct Tile final { int slot_1, slot_2; };

    std::vector<std::vector<Tile>> m_tiles_;
    COORD m_coord_{};

    Grid(const Grid& t_to_copy) = default;
    Grid(Grid&& t_to_move) noexcept = default;
    Grid& operator=(const Grid& t_to_copy) = default;
    Grid& operator=(Grid&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_GRID_HPP