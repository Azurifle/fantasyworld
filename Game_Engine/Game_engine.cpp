#include "stdafx.h"
#include "Game_engine.hpp"

namespace G6037599
{
  //___ static ___________________________________________________________
  void Game_engine::start()
  {

  }

  void Game_engine::limit_interval(int& t_number, const int t_min, const int t_max)
  {
    if (t_number < t_min)
      t_number = t_min;
    else if (t_number > t_max)
      t_number = t_max;
  }

}//G6037599