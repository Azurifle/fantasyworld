#ifndef G6037599_TEST_UNITS_HPP
#define G6037599_TEST_UNITS_HPP
#pragma once
#include "Week_09/Vec3.hpp"
#include "Week_09/Vec4.hpp"

namespace G6037599
{
  class Mat4;

  class Test_units final
  {
  public:
    static void test_case(const std::string& t_operator
      , double t_actual, double t_expected);
    static void test_case(const std::string& t_operator
      , int t_actual, int t_expected);
    static void test_case(const std::string& t_operator
      , bool t_actual, bool t_expected);
    static void show_test_case(const std::string& t_operator
      , const std::string& t_expected, bool t_condition);

    static void mat4_test_unit();

    ~Test_units() = default;
  private:
    Test_units() = default;
    Test_units(const Test_units& t_to_copy) = default;
    Test_units(Test_units&& t_to_move) noexcept = default;
    Test_units& operator = (const Test_units& t_to_copy) = default;
    Test_units& operator = (Test_units&& t_to_move) noexcept = default;

    static void show_header(const std::string& t_header, char t_delim);
    static void mat4_test_case(const std::string& t_operator
      , const Mat4& t_actual, const Mat4& t_expected
      , bool t_shows_as_float = true, bool t_presses_continue = false);
    static void mat4_test_mutiplications(Mat4& t_mat);
    static void mat4_test_transformations(Mat4& t_mat);
    static void vec3_f_test_case(const std::string& t_operator
      , const Vec3<float>& t_actual, const Vec3<float>& t_expected);
    static void vec4_f_test_case(const std::string& t_operator
      , const Vec4<float>& t_actual, const Vec4<float>& t_expected);
  };
}//G6037599

#endif //G6037599_DEMO_CENTER_HPP