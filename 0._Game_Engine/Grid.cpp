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

    std::vector<char> img(DATA_OFFSET - HEADER_SIZE); puts("read each BGR");//***
    bmp.read(img.data(), img.size());

    const unsigned BGR = 3, DATA_SIZE = (WIDTH * BGR + BGR & ~BGR) * HEIGHT;
    img.resize(DATA_SIZE);
    bmp.read(img.data(), img.size());

    m_tiles_.resize(WIDTH, std::vector<Tile>(HEIGHT, Tile{ 0, 0 }));

    puts("get each BGR");//***
    for (auto i = DATA_SIZE - BGR -1; i >= 0; i -= BGR)
    {
      enum Enum{B, G, R};
      std::cout << "B: " << int(img[i+ B] & 0xff) << " G: " << int(img[i + G] & 0xff)
        << " R: " << int(img[i + R] & 0xff) << std::endl;
    }
  }
}//G6037599