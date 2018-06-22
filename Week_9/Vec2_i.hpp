#ifndef G6037599_VEC2_I_HPP
#define G6037599_VEC2_I_HPP
#pragma once
#include "Vec_n_i.hpp"

namespace G6037599
{
  class Vec2_i final: Vec_n_i
  {
  public:
    static const Vec2_i ZEROS, ONES;

    static void test_unit();

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

    std::string to_string() const override;
    double squared_size() const override;
    void normalize() override;

    int dot(const Vec2_i& t_other) const;
    int cross(const Vec2_i& t_other) const;
    Vec2_i get_det() const;
    double radian_angle() const;
    double radian_angle_to(const Vec2_i& t_other) const;
  private:
    static void test_case(const std::string& t_operator
      , const Vec2_i& t_actual, const Vec2_i& t_expected);
    static void test_copy_n_assign(const Vec2_i& t_v1, Vec2_i& t_v2);
    static void test_basic_operators(const Vec2_i& t_v1, const Vec2_i& t_v2);
    static void test_vector_operators(Vec2_i& t_v1, const Vec2_i& t_v2);
    static void test_other_operators(Vec2_i& t_v1, Vec2_i& t_v2);
    static void test_boolean_operators(const Vec2_i& t_v1, const Vec2_i& t_v2);
  };
}//G6037599

#endif //G6037599_VEC2_I_HPP