#ifndef G6037599_GRID_HPP
#define G6037599_GRID_HPP
#pragma once

namespace G6037599
{
  class Grid final
  {
  public:
    enum Enum { NO_TILE, NO_GAME_OBJECT, COLS_PER_TILE = 3};
    static const COORD NOT_SPAWN;

    Grid(const COORD& t_start_coord, const COORD& t_end_coord);
    ~Grid() = default;

    void load(const std::string& t_bmp_path);
    void print() const;
    COORD spawns(int t_id, const std::string& t_symbol);
  private:
    struct Tile final { int slot_1, slot_2; };

    std::vector<std::vector<Tile>> m_tiles_;
    COORD m_start_coord_{}, m_end_coord_{}, m_print_coord_{};

    Grid(const Grid& t_to_copy) = default;
    Grid(Grid&& t_to_move) noexcept = default;
    Grid& operator=(const Grid& t_to_copy) = default;
    Grid& operator=(Grid&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_GRID_HPP