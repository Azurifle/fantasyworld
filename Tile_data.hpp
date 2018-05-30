#ifndef TILE_DATA
#define TILE_DATA
#pragma once

namespace G6037599
{
  class Tile_data
  {
  public:
    const int ID;

    Tile_data();
    explicit Tile_data(const COORD& t_pos);
    ~Tile_data() = default;
    Tile_data(const Tile_data& t_to_copy) = default;
    Tile_data& operator=(const Tile_data& t_to_copy) = default;

    COORD get_pos() const;

    void set_pos(const COORD& t_pos);
  private:
    COORD m_pos_ = { 0, 0 };
    static int m_id_count_;
  };
}//G6037599

#endif //TILE_DATA