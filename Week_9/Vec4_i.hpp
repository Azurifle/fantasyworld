#ifndef G6037599_VEC4_I_HPP
#define G6037599_VEC4_I_HPP
#pragma once
#include "Vec_n_i.hpp"

namespace G6037599
{
  class Vec4_i final : Vec_n_i
  {
  public:
    static const Vec4_i ZEROS, ONES, UP;

    static void test_unit();

    int x, y, z, t;

    Vec4_i();
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
  private:
    static void test_case(const std::string& t_operator
      , const Vec4_i& t_actual, const Vec4_i& t_expected);
    static void test_copy_n_assign(const Vec4_i& t_v1, Vec4_i& t_v2);
    static void test_basic_operators(const Vec4_i& t_v1, const Vec4_i& t_v2);
    static void test_vector_operators(Vec4_i& t_v1, const Vec4_i& t_v2);
    static void test_other_operators(Vec4_i& t_v1, Vec4_i& t_v2);
    static void test_boolean_operators(const Vec4_i& t_v1, const Vec4_i& t_v2);
  };
}//G6037599

#endif //G6037599_VEC4_I_HPP