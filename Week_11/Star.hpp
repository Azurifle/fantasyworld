#ifndef G6037599_STAR_HPP
#define G6037599_STAR_HPP
#pragma once
#include "Triangle.hpp"

namespace G6037599
{
  class Star
  {
  public://not same start_pos, end_pos, rotate_speed+change color speed (t_blink_rate), spawn time
    explicit Star(const Vec3<float>& t_start_pos = Vec3<float>(0)
      , const Vec3<float>& t_end_pos = Vec3<float>(1, 1, 0)
      , float t_rotate_speed = 180, float t_blink_rate = 1);
    ~Star() = default;
    Star(const Star& t_to_copy) = default;
    Star(Star&& t_to_move) noexcept = default;
    Star& operator = (const Star& t_to_copy) = default;
    Star& operator = (Star&& t_to_move) noexcept = default;

    void update(float t_delta_seconds);//same move_speed & scale_speed (follow distance)
  private:
    std::vector<Triangle> m_5_tips_{};
    Vec3<float> m_pos_{}, m_end_pos_{}, m_scale_{};
    float m_rotate_speed_, m_z_degrees_;
  };
}//G6037599

#endif //G6037599_STAR_HPP