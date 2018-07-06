#ifndef G6037599_TRIANGLE_HPP
#define G6037599_TRIANGLE_HPP
#pragma once
#include "Week_09/Vec3.hpp"

namespace G6037599
{
  class Triangle final
  {
  public:
    Vec3<float> pos{}, scale{};
    float degrees_per_sec;

    explicit Triangle(const Vec3<float>& t_pos = Vec3<float>(0)
      , const Vec3<float>& t_scale = Vec3<float>(1)
      , float t_degrees_per_sec = 180);
    ~Triangle() = default;
    Triangle(const Triangle& t_to_copy) = default;
    Triangle(Triangle&& t_to_move) noexcept = default;
    Triangle& operator = (const Triangle& t_to_copy) = default;
    Triangle& operator = (Triangle&& t_to_move) noexcept = default;

    void update(float t_delta_seconds);
  private:
    float m_x_degrees_;

    static void paint_pos(const Vec3<float>& t_pos, const Vec3<float>& t_rgb);
  };
}//G6037599

#endif //G6037599_TRIANGLE_HPP