#ifndef G6037599_VEC2_I_HPP
#define G6037599_VEC2_I_HPP
#pragma once

namespace G6037599
{
  class Vec2_i final
  {
  public:
    int x, y;//if there is no setter constraint make it public

    Vec2_i() = default;
    ~Vec2_i() = default;
    Vec2_i(int t_x, int t_y);
  private:
    Vec2_i(const Vec2_i& t_to_copy) = default;
    Vec2_i(Vec2_i&& t_to_move) noexcept = default;
    Vec2_i& operator = (const Vec2_i& t_to_copy) = default;
    Vec2_i& operator = (Vec2_i&& t_to_move) noexcept = default;
  };

  void vec2_i_demo();
  void print(const Vec2_i& t_vector);
}//G6037599

#endif //G6037599_VEC2_I_HPP