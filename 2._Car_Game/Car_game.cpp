#include "stdafx.h"
#include "Car_game.hpp"

namespace G6037599
{
  //___ static _____________________________________________
  void Car_game::run()
  {
    REQUIRE(Game_engine::is_running());
    Car_game game{};

    while (true)
    {
      const auto A_QUARTER_SECOND = 250;
      Sleep(A_QUARTER_SECOND);
      switch (Game_engine::get_key())
      {
      case Game_engine::KEY_NO_PRESS: break;
      case Game_engine::KEY_ESC: return;
      default:;
      }
    }//game loop

    /*std::vector<std::vector<int>> map;
    map.push_back(std::vector<int>({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }));
    map.push_back(std::vector<int>({ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }));
    map.push_back(std::vector<int>({ 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0 }));
    map.push_back(std::vector<int>({ 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0 }));
    map.push_back(std::vector<int>({ 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0 }));
    map.push_back(std::vector<int>({ 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0 }));
    map.push_back(std::vector<int>({ 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0 }));
    map.push_back(std::vector<int>({ 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0 }));
    map.push_back(std::vector<int>({ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }));
    map.push_back(std::vector<int>({ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }));

    for (auto row : map)
    {
      for (auto i : row)
      {
        std::cout << ' ';
        switch (i)
        {
        case 0: std::cout << ' '; break;
        default: std::cout << '-'; break;
        }
      }
      std::cout << std::endl;
    }
    _getch();*/
  }
}//G6037599