#ifndef G6037599_VEC_TEST_UNITS_HPP
#define G6037599_VEC_TEST_UNITS_HPP
#pragma once
#include "Vec3_i.hpp"
#include "Vec4_i.hpp"

namespace G6037599
{
  class Vec_n;
  class Vec2_i;

  class Vec_test_units
  {
  public:
    static void run();

    ~Vec_test_units() = default;
  private:
    static void show_header(int t_vector_type);
    static void show(const char* t_name, const Vec_n& t_vec_i);
    static void show(const Vec_n& t_v1, const Vec_n& t_v2);
    static void test_sizes_n_normalize(Vec_n& t_v1, double t_size, double t_squared_size);

    static void vec2_test_unit();
    static void vec2_test_case(const std::string& t_operator, const Vec2_i& t_actual, const Vec2_i& t_expected);
    static void vec2_test_copy_n_assign(const Vec2_i& t_v1, Vec2_i& t_v2);
    static void vec2_test_basic_operators(const Vec2_i& t_v1, const Vec2_i& t_v2);
    static void vec2_test_vector_operators(Vec2_i& t_v1, const Vec2_i& t_v2);
    static void vec2_test_other_operators(Vec2_i& t_v1, Vec2_i& t_v2);
    static void vec2_test_boolean_operators(const Vec2_i& t_v1, const Vec2_i& t_v2);

    static void vec3_test_unit();
    static void vec3_test_case(const std::string& t_operator, const Vec3_i& t_actual, const Vec3_i& t_expected);
    static void vec3_test_copy_n_assign(const Vec3_i& t_v1, Vec3_i& t_v2);
    static void vec3_test_basic_operators(const Vec3_i& t_v1, const Vec3_i& t_v2);
    static void vec3_test_vector_operators(Vec3_i& t_v1, const Vec3_i& t_v2);
    static void vec3_test_other_operators(Vec3_i& t_v1, Vec3_i& t_v2);
    static void vec3_test_boolean_operators(const Vec3_i& t_v1, const Vec3_i& t_v2);

    static void vec4_test_unit();
    static void vec4_test_case(const std::string& t_operator, const Vec4_i& t_actual, const Vec4_i& t_expected);
    static void vec4_test_copy_n_assign(const Vec4_i& t_v1, Vec4_i& t_v2);
    static void vec4_test_basic_operators(const Vec4_i& t_v1, const Vec4_i& t_v2);
    static void vec4_test_vector_operators(Vec4_i& t_v1, const Vec4_i& t_v2);
    static void vec4_test_other_operators(Vec4_i& t_v1, Vec4_i& t_v2);
    static void vec4_test_boolean_operators(const Vec4_i& t_v1, const Vec4_i& t_v2);

    Vec_test_units() = default;
    Vec_test_units(const Vec_test_units& t_to_copy) = default;
    Vec_test_units(Vec_test_units&& t_to_move) noexcept = default;
    Vec_test_units& operator = (const Vec_test_units& t_to_copy) = default;
    Vec_test_units& operator = (Vec_test_units&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_VEC_TEST_UNITS_HPP