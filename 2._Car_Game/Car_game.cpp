#include "stdafx.h"
#include "Car_game.hpp"

namespace G6037599
{
  //___ static _____________________________________________
  void Car_game::run()
  {
    std::vector<std::vector<int>> map;
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
    _getch();


  }
}//G6037599