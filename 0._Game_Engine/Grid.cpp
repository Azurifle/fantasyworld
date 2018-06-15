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

    const auto WIDTH = *reinterpret_cast<short *>(&header[18])
      , HEIGHT = *reinterpret_cast<short *>(&header[22]);

    const short BGR = 3, DATA_SIZE = (WIDTH * BGR + BGR & ~BGR) * HEIGHT;
    std::vector<char> inverse_row_img(DATA_SIZE);
    bmp_stream.read(inverse_row_img.data(), inverse_row_img.size());

    m_tiles_.resize(HEIGHT, std::vector<Tile>(WIDTH, Tile{NO_TILE, NO_TILE}));

    enum Enum { B, G, R, COLOR_VALUE = 255, ROW_PADDING = 2 };
    for (short row = 0; row < HEIGHT; ++row)
    {
      for (short col = 0; col < WIDTH; ++col)
      {
        const auto INDEX = (HEIGHT -1 -row) * (WIDTH * BGR + ROW_PADDING) + col * BGR
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

    const short LAST_PRINT_COLS = m_start_coord_.X + WIDTH * COLS_PER_TILE - 1;
    if(LAST_PRINT_COLS >= m_end_coord_.X)
    {
      m_print_coord_.X = m_start_coord_.X;
      m_print_size_.X = WIDTH - (m_end_coord_.X - LAST_PRINT_COLS);
    }
    else
    {
      const short COLS_BEFORE = (m_end_coord_.X - m_start_coord_.X + 1 
        - WIDTH * COLS_PER_TILE) / 2;
      m_print_coord_.X = m_start_coord_.X + COLS_BEFORE;
      m_print_size_.X = WIDTH;
    }

    const short LAST_PRINT_ROWS = m_start_coord_.Y + HEIGHT - 1;
    if (LAST_PRINT_ROWS >= m_end_coord_.Y)
    {
      m_print_coord_.Y = m_start_coord_.Y;
      m_print_size_.Y = HEIGHT - (m_end_coord_.Y - LAST_PRINT_ROWS);
    }
    else
    {
      const short ROWS_BEFORE = (m_end_coord_.Y - m_start_coord_.Y + 1
        - HEIGHT) / 2;
      m_print_coord_.Y = m_start_coord_.Y + ROWS_BEFORE;
      m_print_size_.Y = HEIGHT;
    }
  }

  void Grid::print() const
  {
    short row = 0;
    do
    {
      Game_engine::set_cursor({ m_print_coord_.X, m_print_coord_.Y + row });

      for (short col = 0; col < m_print_size_.X; ++col)
      {
        switch (m_tiles_[row][col].slot_1)
        {
        case NO_TILE: std::cout << "##+"; break;
        default: std::cout << "   ";
        }
      }
      ++row;
    } while (row < m_print_size_.Y);
  }

  COORD Grid::spawns(const int t_id, const std::string& t_symbol)
  {
    REQUIRE(t_id > NO_GAME_OBJECT);
    COORD pos;
    do
    {
      pos.Y = static_cast<short>(rand()) % m_print_size_.Y;
      pos.X = static_cast<short>(rand()) % m_print_size_.X;
      switch (Game_engine::get_key())
      {
      case 0: break;
      default: switch (rand() & 3) 
        { case 0: return NOT_SPAWN; default:; }//change to find nearest available tile if have time
      }
    } while (m_tiles_[pos.Y][pos.X].slot_1 != NO_GAME_OBJECT
      || m_tiles_[pos.Y][pos.X].slot_2 != NO_GAME_OBJECT);

    m_tiles_[pos.Y][pos.X].slot_1 = t_id;
    Game_engine::set_cursor(get_coord(pos));
    std::cout << t_symbol;

    return pos;
  }

  void Grid::despawns(const COORD& t_pos, const int t_id)
  {
    REQUIRE(t_pos.X != NOT_SPAWN.X);
    REQUIRE(t_id > NO_GAME_OBJECT);

    if (m_tiles_[t_pos.Y][t_pos.X].slot_1 == t_id)
    {
      m_tiles_[t_pos.Y][t_pos.X].slot_1 = NO_GAME_OBJECT;

      Game_engine::set_cursor(get_coord(t_pos));
      std::cout << '.';
    }
    else
    {
      REQUIRE(m_tiles_[t_pos.Y][t_pos.X].slot_2 == t_id);
      m_tiles_[t_pos.Y][t_pos.X].slot_2 = NO_GAME_OBJECT;

      Game_engine::set_cursor(get_coord(t_pos, true));
      std::cout << ' ';
    }
  }

  bool Grid::moved(COORD& t_pos, const int t_id, const std::string& t_symbol, COORD t_moved)
  {
    REQUIRE(t_pos.X != NOT_SPAWN.X && t_pos.Y != NOT_SPAWN.Y);
    REQUIRE(t_id > NO_GAME_OBJECT);

    t_moved.X = Game_engine::limit_interval(t_moved.X, 0, m_print_size_.X);
    t_moved.Y = Game_engine::limit_interval(t_moved.Y, 0, m_print_size_.Y);

    switch (m_tiles_[t_moved.Y][t_moved.X].slot_1)
    {
    case NO_GAME_OBJECT: m_tiles_[t_moved.Y][t_moved.X].slot_1 = t_id;
      despawns(t_pos, t_id);
      Game_engine::set_cursor(get_coord(t_moved));
      std::cout << t_symbol;
      break;
    case NO_TILE: return false;
    default: switch (m_tiles_[t_moved.Y][t_moved.X].slot_2)
      {
      case NO_GAME_OBJECT: m_tiles_[t_moved.Y][t_moved.X].slot_2 = t_id;
        despawns(t_pos, t_id);
        Game_engine::set_cursor(get_coord(t_moved, true));
        std::cout << t_symbol;
        break;
      default: return false;
      }
    }
    t_pos = t_moved;
    return true;
  }

  void Grid::set(const COORD& t_pos, const int t_id, const int t_new_id)
  {
    REQUIRE(t_pos.X != NOT_SPAWN.X && t_pos.Y != NOT_SPAWN.Y);
    REQUIRE(t_id > NO_GAME_OBJECT); REQUIRE(t_new_id > NO_GAME_OBJECT);
    REQUIRE(t_id != t_new_id);

    if (m_tiles_[t_pos.Y][t_pos.X].slot_1 == t_id)
    {
      m_tiles_[t_pos.Y][t_pos.X].slot_1 = t_new_id;
    }
    else
    {
      REQUIRE(m_tiles_[t_pos.Y][t_pos.X].slot_2 == t_id);
      m_tiles_[t_pos.Y][t_pos.X].slot_2 = t_new_id;
    }
  }

  //___ private _____________________________________________
  COORD Grid::get_coord(const COORD& t_pos, const bool t_is_slot_2) const
  {
    REQUIRE(0 <= t_pos.X); REQUIRE(t_pos.X < m_print_size_.X);
    REQUIRE(0 <= t_pos.Y); REQUIRE(t_pos.Y < m_print_size_.Y);

    return COORD{ m_print_coord_.X + t_pos.X * COLS_PER_TILE + (t_is_slot_2 ? 1: 0)
      , m_print_coord_.Y + t_pos.Y };
  }
}//G6037599