#ifndef G6037599_GRID_HPP
#define G6037599_GRID_HPP
#pragma once

namespace G6037599
{
  class Grid final
  {
  public:
    struct Tile final { int owner_id, second_id; };

    Grid(const COORD& t_coord, int t_grid_cols, int t_grid_rows);
    ~Grid() = default;
  private:
    std::vector<std::vector<Tile>> m_tiles_;
    COORD m_coord_{};

    Grid(const Grid& t_to_copy) = default;
    Grid(Grid&& t_to_move) noexcept = default;
    Grid& operator=(const Grid& t_to_copy) = default;
    Grid& operator=(Grid&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_GRID_HPP