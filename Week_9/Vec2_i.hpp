#ifndef G6037599_VEC2_I_HPP
#define G6037599_VEC2_I_HPP
#pragma once
#include "Vec_n.hpp"

namespace G6037599
{
  class Vec2_i final: public Vec_n
  {
  public:
    enum Type { ZEROS, ONES };

    int x, y;//if there is no setter constraint make it public

    explicit Vec2_i(Type t_typ = ZEROS);
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

    std::string to_string() const override;
    double squared_size() const override;
    void normalize() override;

    int dot(const Vec2_i& t_other) const;
    int cross(const Vec2_i& t_other) const;
    Vec2_i get_det() const;
    double radian_angle() const;
    double radian_angle_to(const Vec2_i& t_other) const;
  };
}//G6037599

#endif //G6037599_VEC2_I_HPP