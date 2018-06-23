#ifndef G6037599_VEC4_I_HPP
#define G6037599_VEC4_I_HPP
#pragma once
#include "Vec_n.hpp"

namespace G6037599
{
  class Vec4_i final : public Vec_n
  {
  public:
    enum Type { ZEROS, ONES, UP };

    int x, y, z, t;

    explicit Vec4_i(Type t_typ = ZEROS);
    ~Vec4_i() = default;
    Vec4_i(int t_x, int t_y, int t_z, int t_t);
    Vec4_i(const Vec4_i& t_to_copy) = default;
    Vec4_i(Vec4_i&& t_to_move) noexcept = default;
    Vec4_i& operator = (const Vec4_i& t_to_copy) = default;
    Vec4_i& operator = (Vec4_i&& t_to_move) noexcept = default;

    Vec4_i operator += (const Vec4_i& t_other);
    Vec4_i operator -= (const Vec4_i& t_other);
    Vec4_i operator *= (int t_scalar);
    Vec4_i operator /= (int t_scalar);

    Vec4_i operator << (const Vec4_i& t_other) const;
    Vec4_i operator + (const Vec4_i& t_other) const;
    Vec4_i operator - (const Vec4_i& t_other) const;
    Vec4_i operator * (int t_scalar) const;
    Vec4_i operator / (int t_scalar) const;

    bool operator <= (const Vec4_i& t_other) const;
    bool operator >= (const Vec4_i& t_other) const;
    bool operator == (const Vec4_i& t_other) const;
    bool operator != (const Vec4_i& t_other) const;
    bool operator < (const Vec4_i& t_other) const;
    bool operator > (const Vec4_i& t_other) const;

    std::string to_string() const override;
    double squared_size() const override;
    void normalize() override;

    int dot(const Vec4_i& t_other) const;
    double radian_angle_to(const Vec4_i& t_other) const;
  };
}//G6037599

#endif //G6037599_VEC4_I_HPP