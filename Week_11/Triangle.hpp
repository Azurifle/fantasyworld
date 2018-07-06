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
    float degree_angular_velocity;

    explicit Triangle(const Vec3<float>& t_pos = Vec3<float>(0)
      , const Vec3<float>& t_scale = Vec3<float>(1)
      , float t_degree_angular_velocity = 180);
    ~Triangle() = default;
    Triangle(const Triangle& t_to_copy) = default;
    Triangle(Triangle&& t_to_move) noexcept = default;
    Triangle& operator = (const Triangle& t_to_copy) = default;
    Triangle& operator = (Triangle&& t_to_move) noexcept = default;

    void render();
  private:
    float m_x_degree_;

    static void paint_pos(const Vec3<float>& t_pos, const Vec3<float>& t_rgb);
  };
}//G6037599

#endif //G6037599_TRIANGLE_HPP