#include "stdafx.h"
#include "Grid.hpp"
#include "Game_engine.hpp"

namespace G6037599
{
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

    std::ifstream bmp(t_bmp_path, std::ios::binary);

    const size_t HEADER_SIZE = 54;
    std::array<char, HEADER_SIZE> header;
    bmp.read(header.data(), header.size());

    const auto DATA_OFFSET = *reinterpret_cast<unsigned *>(&header[10])
      , WIDTH = *reinterpret_cast<unsigned *>(&header[18])
      , HEIGHT = *reinterpret_cast<unsigned *>(&header[22]);

    std::vector<char> img(DATA_OFFSET - HEADER_SIZE);
    bmp.read(img.data(), img.size());

    const auto ROW_PADDED = WIDTH * 3 + 3 & ~3
      , DATA_SIZE = ROW_PADDED * HEIGHT;
    img.resize(DATA_SIZE);
    bmp.read(img.data(), img.size());

    for (auto i = DATA_SIZE - 4; i >= 0; i -= 3)
    {
      const auto TEMP = img[i];
      img[i] = img[i + 2];
      img[i + 2] = TEMP;

      std::cout << "R: " << int(img[i] & 0xff) << " G: " << int(img[i + 1] & 0xff) << " B: " << int(img[i + 2] & 0xff) << std::endl;
    }
   
    m_tiles_.resize(m_end_coord_.X - m_start_coord_.X
      , std::vector<Tile>(m_end_coord_.Y - m_start_coord_.Y, Tile{ 0, 0 }));
  }
}//G6037599