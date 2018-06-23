#ifndef G6037599_VEC3_I_HPP
#define G6037599_VEC3_I_HPP
#pragma once
#include "Vec_n.hpp"

namespace G6037599
{
  class Vec3_i final : public Vec_n
  {
  public:
    enum Type { ZEROS, ONES, UP };

    int x, y, z;

    explicit Vec3_i(Type t_typ = ZEROS);
    ~Vec3_i() = default;
    Vec3_i(int t_x, int t_y, int t_z);
    Vec3_i(const Vec3_i& t_to_copy) = default;
    Vec3_i(Vec3_i&& t_to_move) noexcept = default;
    Vec3_i& operator = (const Vec3_i& t_to_copy) = default;
    Vec3_i& operator = (Vec3_i&& t_to_move) noexcept = default;

    Vec3_i operator += (const Vec3_i& t_other);
    Vec3_i operator -= (const Vec3_i& t_other);
    Vec3_i operator *= (int t_scalar);
    Vec3_i operator /= (int t_scalar);

    Vec3_i operator << (const Vec3_i& t_other) const;
    Vec3_i operator + (const Vec3_i& t_other) const;
    Vec3_i operator - (const Vec3_i& t_other) const;
    Vec3_i operator * (int t_scalar) const;
    Vec3_i operator / (int t_scalar) const;

    bool operator <= (const Vec3_i& t_other) const;
    bool operator >= (const Vec3_i& t_other) const;
    bool operator == (const Vec3_i& t_other) const;
    bool operator != (const Vec3_i& t_other) const;
    bool operator < (const Vec3_i& t_other) const;
    bool operator > (const Vec3_i& t_other) const;

    std::string to_string() const override;
    double squared_size() const override;
    void normalize() override;

    int dot(const Vec3_i& t_other) const;
    Vec3_i cross(const Vec3_i& t_other) const;
    int cross(const Vec3_i& t_v2, const Vec3_i& t_v3) const;
    Vec3_i radian_angles() const;
    double radian_angle_to(const Vec3_i& t_other) const;
  };
}//G6037599

#endif //G6037599_VEC3_I_HPP