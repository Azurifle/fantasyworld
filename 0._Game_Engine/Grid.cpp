#include "stdafx.h"
#include "Grid.hpp"
#include "Game_engine.hpp"

namespace G6037599
{
  //___ static _____________________________________________
  const COORD Grid::NOT_SPAWN = { -1, -1 };

  //___ (de)constructors _____________________________________________
  Grid::Grid(const COORD& t_start_coord, const COORD& t_end_coord)
    : m_start_coord_(t_start_coord), m_end_coord_(t_end_coord)
  {
    REQUIRE(0 <= t_start_coord.X); REQUIRE(t_end_coord.X <= Game_engine::CMD_LAST_COLS);
    REQUIRE(0 <= t_start_coord.Y); REQUIRE(t_end_coord.Y <= Game_engine::CMD_LAST_ROWS);
    REQUIRE(t_start_coord.X < t_end_coord.X);
    REQUIRE(t_start_coord.Y < t_end_coord.Y);
  }

  //___ public _____________________________________________
  void Grid::load(const std::string& t_bmp_path)
  {
    //https://stackoverflow.com/questions/9296059/read-pixel-value-in-bmp-file

    std::ifstream bmp_stream(t_bmp_path, std::ios::binary);
    REQUIRE(bmp_stream.is_open());//should change to popup warning later

    const size_t HEADER_SIZE = 54;
    std::array<char, HEADER_SIZE> header;
    bmp_stream.read(header.data(), header.size());

    const auto WIDTH = *reinterpret_cast<unsigned *>(&header[18])
      , HEIGHT = *reinterpret_cast<unsigned *>(&header[22]);

    const unsigned BGR = 3, DATA_SIZE = (WIDTH * BGR + BGR & ~BGR) * HEIGHT;
    std::vector<char> inverse_row_img(DATA_SIZE);
    bmp_stream.read(inverse_row_img.data(), inverse_row_img.size());

    m_tiles_.resize(HEIGHT, std::vector<Tile>(WIDTH, Tile{NO_TILE, NO_TILE}));

    enum Enum { B, G, R, COLOR_VALUE = 255, ROW_PADDING = 2 };
    for (unsigned row = 0; row < HEIGHT; ++row)
    {
      for (unsigned col = 0; col < WIDTH; ++col)
      {
        const unsigned INDEX = (HEIGHT -1 -row) * (WIDTH * BGR + ROW_PADDING) + col * BGR
          , CAN_MOVE_B = 176, CAN_MOVE_G = 228, CAN_MOVE_R = 239;
        
        if(static_cast<unsigned>(inverse_row_img[INDEX + B] & COLOR_VALUE) == CAN_MOVE_B
          && static_cast<unsigned>(inverse_row_img[INDEX + G] & COLOR_VALUE) == CAN_MOVE_G
          && static_cast<unsigned>(inverse_row_img[INDEX + R] & COLOR_VALUE) == CAN_MOVE_R)
        {
          m_tiles_[row][col].slot_1 = NO_GAME_OBJECT;
          m_tiles_[row][col].slot_2 = NO_GAME_OBJECT;
        }
      }//col loop
    }//row loop

    if(m_start_coord_.X + WIDTH * COLS_PER_TILE - 1 
      >= static_cast<unsigned>(m_end_coord_.X))
    {
      m_print_coord_.X = m_start_coord_.X;
    }
    else
    {
      const auto COLS_BEFORE = (m_end_coord_.X - m_start_coord_.X + 1 
        - WIDTH * COLS_PER_TILE) / 2;
      m_print_coord_.X = static_cast<short>(m_start_coord_.X + COLS_BEFORE);
    }

    if (m_start_coord_.Y + HEIGHT - 1 >= 
      static_cast<unsigned>(m_end_coord_.Y))
    {
      m_print_coord_.Y = m_start_coord_.Y;
    }
    else
    {
      const auto ROWS_BEFORE = (m_end_coord_.Y - m_start_coord_.Y + 1 
        - HEIGHT) / 2;
      m_print_coord_.Y = static_cast<short>(m_start_coord_.Y + ROWS_BEFORE);
    }
  }

  void Grid::print() const
  {
    short row = 0;
    do
    {
      Game_engine::set_cursor({ m_print_coord_.X, m_print_coord_.Y + row });

      for (unsigned col = 0; col < m_tiles_[row].size() 
        && m_print_coord_.X + col* COLS_PER_TILE <= 
        static_cast<unsigned>(m_end_coord_.X); ++col)
      {
        switch (m_tiles_[row][col].slot_1)
        {
        case NO_TILE: std::cout << "##+"; break;
        default: std::cout << ".  ";
        }
      }
      ++row;
    } while (static_cast<unsigned>(row) < m_tiles_.size() 
      && m_print_coord_.Y + row <= m_end_coord_.Y);
  }

  COORD Grid::spawns(const int t_id, const std::string& t_symbol)
  {
    COORD pos;
    do
    {
      pos.Y = static_cast<short>(rand() % m_tiles_.size());
      pos.X = static_cast<short>(rand() % m_tiles_[0].size());
      switch (Game_engine::get_key())
      {
      case 0: break;
      default: switch (rand() & 3) 
        { case 0: return NOT_SPAWN; default:; }//change to find nearest available tile if have time
      }
    } while (m_tiles_[pos.Y][pos.X].slot_1 != NO_GAME_OBJECT
      || m_tiles_[pos.Y][pos.X].slot_2 != NO_GAME_OBJECT);

    m_tiles_[pos.Y][pos.X].slot_1 = t_id;
    Game_engine::set_cursor(COORD{ m_print_coord_.X + pos.X * COLS_PER_TILE
      , m_print_coord_.Y + pos.Y });
    std::cout << t_symbol;

    return pos;
  }
}//G6037599