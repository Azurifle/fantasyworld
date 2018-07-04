#ifndef G6037599_TRIANGLE_HPP
#define G6037599_TRIANGLE_HPP
#pragma once
#include "Week_09/Vec3.hpp"

namespace G6037599
{
  class Triangle final
  {
  public:
    Triangle();
    ~Triangle() = default;
    Triangle(const Triangle& t_to_copy) = default;
    Triangle(Triangle&& t_to_move) noexcept = default;
    Triangle& operator = (const Triangle& t_to_copy) = default;
    Triangle& operator = (Triangle&& t_to_move) noexcept = default;

    void draw();
  private:
    Vec3<float> m_translate_{};
    Vec3<float> m_rotate_{};
    Vec3<float> m_scale_{};
  };
}//G6037599

#endif //G6037599_TRIANGLE_HPP