#ifndef G6037599_VEC2_I_HPP
#define G6037599_VEC2_I_HPP
#pragma once

namespace G6037599
{
  void vec2_i_test_unit();

  class Vec2_i final
  {
  public:
    static const Vec2_i ZEROS, ONES;

    int x, y;//if there is no setter constraint make it public

    Vec2_i();
    ~Vec2_i() = default;
    Vec2_i(int t_x, int t_y);
    Vec2_i(const Vec2_i& t_to_copy) = default;
    Vec2_i(Vec2_i&& t_to_move) noexcept = default;
    Vec2_i& operator = (const Vec2_i& t_to_copy) = default;
    Vec2_i& operator = (Vec2_i&& t_to_move) noexcept = default;

    Vec2_i operator += (const Vec2_i& t_other);
    Vec2_i operator -= (const Vec2_i& t_other);
    Vec2_i operator *= (int t_scalar);
    Vec2_i operator /= (int t_scalar);

    Vec2_i operator << (const Vec2_i& t_other) const;
    Vec2_i operator + (const Vec2_i& t_other) const;
    Vec2_i operator - (const Vec2_i& t_other) const;
    Vec2_i operator * (int t_scalar) const;
    Vec2_i operator / (int t_scalar) const;

    bool operator <= (const Vec2_i& t_other) const;
    bool operator >= (const Vec2_i& t_other) const;
    bool operator == (const Vec2_i& t_other) const;
    bool operator != (const Vec2_i& t_other) const;
    bool operator < (const Vec2_i& t_other) const;
    bool operator > (const Vec2_i& t_other) const;

    std::string to_string() const;
    int dot(const Vec2_i& t_other) const;
    int cross(const Vec2_i& t_other) const;
    double size() const;
    double squared_size() const;
    Vec2_i normalize();
    double radian_angle() const;
    double radian_angle_to(const Vec2_i& t_other) const;
  };
}//G6037599

#endif //G6037599_VEC2_I_HPP