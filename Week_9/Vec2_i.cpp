#include "stdafx.h"
#include "Vec2_i.hpp"

namespace G6037599
{
  //___ static _______________________________________________________
  void vec2_i_demo()
  {
    const Vec2_i v1(0, 9);
    const Vec2_i v2(4, 5);

    print(v1);
    print(v2);
  }

  void print(const Vec2_i& t_vector)
  {
    std::cout << '(' << t_vector.x << ',' << t_vector.y << ')' << std::endl;
  }

  //___ (de)constructors/operators ____________________________________
  Vec2_i::Vec2_i(const int t_x, const int t_y) : x(t_x), y(t_y) {}
}//G6037599