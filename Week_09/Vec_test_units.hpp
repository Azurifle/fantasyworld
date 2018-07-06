#ifndef G6037599_VEC_TEST_UNITS_HPP
#define G6037599_VEC_TEST_UNITS_HPP
#pragma once

#include "Vec2.hpp"
#include "Vec3.hpp"
#include "Vec4.hpp"

namespace G6037599
{
  class Vec_test_units
  {
  public:
    static void run();

    ~Vec_test_units() = default;
  private:
    static void show_header(int t_vector_type);
    static void show(const char* t_name, const std::string& t_vec);
    static void show(const std::string& t_v1, const std::string& t_v2);
    static void test_sizes(double t_size, double t_squared_size);

    static void vec2_test_unit();
    static void vec2_test_case(const std::string& t_operator
      , const Vec2<int>& t_actual, const Vec2<int>& t_expected);
    static void vec2_test_copy(const Vec2<int>& t_v1, Vec2<int>& t_v2);
    static void vec2_test_basic_operators(const Vec2<int>& t_v1, const Vec2<int>& t_v2);
    static void vec2_test_vector_operators(Vec2<int>& t_v1, const Vec2<int>& t_v2);
    static void vec2_test_assign_operators(Vec2<int>& t_v1, Vec2<int>& t_v2);
    static void vec2_test_boolean_operators(const Vec2<int>& t_v1, const Vec2<int>& t_v2);

    static void vec3_test_unit();
    static void vec3_test_case(const std::string& t_operator
      , const Vec3<int>& t_actual, const Vec3<int>& t_expected);
    static void vec3_test_copy(const Vec3<int>& t_v1, Vec3<int>& t_v2);
    static void vec3_test_basic_operators(const Vec3<int>& t_v1, const Vec3<int>& t_v2);
    static void vec3_test_vector_operators(Vec3<int>& t_v1, const Vec3<int>& t_v2);
    static void vec3_test_assign_operators(Vec3<int>& t_v1, Vec3<int>& t_v2);
    static void vec3_test_boolean_operators(const Vec3<int>& t_v1, const Vec3<int>& t_v2);

    static void vec4_test_unit();
    static void vec4_test_case(const std::string& t_operator
      , const Vec4<int>& t_actual, const Vec4<int>& t_expected);
    static void vec4_test_copy(const Vec4<int>& t_v1, Vec4<int>& t_v2);
    static void vec4_test_basic_operators(const Vec4<int>& t_v1, const Vec4<int>& t_v2);
    static void vec4_test_vector_operators(Vec4<int>& t_v1, const Vec4<int>& t_v2);
    static void vec4_test_assign_operators(Vec4<int>& t_v1, Vec4<int>& t_v2);
    static void vec4_test_boolean_operators(const Vec4<int>& t_v1, const Vec4<int>& t_v2);

    Vec_test_units() = default;
    Vec_test_units(const Vec_test_units& t_to_copy) = default;
    Vec_test_units(Vec_test_units&& t_to_move) noexcept = default;
    Vec_test_units& operator = (const Vec_test_units& t_to_copy) = default;
    Vec_test_units& operator = (Vec_test_units&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_VEC_TEST_UNITS_HPP