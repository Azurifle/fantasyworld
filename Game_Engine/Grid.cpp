#include "stdafx.h"
#include "Grid.hpp"
#include "Game_engine.hpp"

namespace G6037599
{
  Grid::Grid(const COORD& t_coord, int t_grid_cols, int t_grid_rows)
    : m_coord_(t_coord)
  {
    const auto CMD_COLS_LIMIT = 40, CMD_ROWS_LIMIT = 30, MIN_TILES = 2;
    REQUIRE(0 <= t_coord.X); REQUIRE(t_coord.X <= CMD_COLS_LIMIT);
    REQUIRE(0 <= t_coord.Y); REQUIRE(t_coord.Y <= CMD_ROWS_LIMIT);
    Game_engine::limit_interval(t_grid_cols, MIN_TILES, CMD_COLS_LIMIT - t_coord.X);
    Game_engine::limit_interval(t_grid_rows, MIN_TILES, CMD_ROWS_LIMIT - t_coord.Y);

    m_tiles_.resize(t_grid_cols, std::vector<Tile>(t_grid_rows, Tile{ 0, 0 }));
  }
}//G6037599