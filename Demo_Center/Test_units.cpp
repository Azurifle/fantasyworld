#include "stdafx.h"
#include "Test_units.hpp"
#include "Demo_Center.hpp"
#include "Week_10/Mat4.hpp"

namespace G6037599
{
  // ___ static ___________________________________________________________
  void Test_units::test_case(const std::string& t_operator, const int t_actual
    , const int t_expected)
  {
    show_test_case(t_operator, std::to_string(t_expected)
      , t_actual == t_expected);
  }

  void Test_units::test_case(const std::string& t_operator, const double t_actual
    , const double t_expected)
  {
    show_test_case(t_operator, Demo_center::double_points_string(t_expected)
      , abs(t_actual - t_expected) <= Demo_center::PRECISION);
  }

  void Test_units::test_case(const std::string& t_operator, const bool t_actual
    , const bool t_expected)
  {
    show_test_case(t_operator, t_expected ? "true" : "false"
      , t_actual == t_expected);
  }

  void Test_units::show_test_case(const std::string& t_operator
    , const std::string& t_expected, const bool t_condition)
  {
    std::cout << "  " << t_operator.c_str() << " == " << t_expected.c_str()
      << " ?: " << (t_condition ? "Pass" : "Fail")
      << '.' << std::endl;
  }

  void Test_units::mat4_test_unit()
  {
    show_header("Matrix Test Unit", '=');
    mat4_test_case("A matrix of zeros", Mat4(), Mat4(0), false);
    Mat4 mat(1);
    mat4_test_case("An identity matrix", Mat4::identity(), mat, false, true);

    show_header("Transformations", '-');
    mat4_test_transformations(mat);

    const auto transpose_mat = Mat4::transpose(mat);
    mat4_test_case("Mat4::transpose(mat)", Mat4::transpose(mat), transpose_mat
      , true, true);

    show_header("Inverse", '-');
    mat4_test_case("(mat^-1)^-1", Mat4::inverse(Mat4::inverse(mat)), mat);
    mat4_test_case("mat * mat^-1", mat * Mat4::inverse(mat), Mat4::identity()
      , true, true);

    show_header("Mutiplications", '-');
    mat4_test_mutiplications(mat);
  }

  // ___ private ___________________________________________________________
  void Test_units::show_header(const std::string& t_header, const char t_delim)
  {
    Demo_center::print_centered_header(t_header, t_delim);
    puts("");
  }

  void Test_units::mat4_test_case(const std::string& t_operator
    , const Mat4& t_actual, const Mat4& t_expected
    , const bool t_shows_as_float, const bool t_presses_continue)
  {
    show_test_case(t_operator, "Mat4" + t_expected.to_string(t_shows_as_float)
      , t_actual == t_expected);

    switch (t_presses_continue) 
    { 
      case true: Demo_center::press_to_continue(); break;
      default: puts("");
    }
  }

  void Test_units::mat4_test_transformations(Mat4& t_mat)
  {
    const Vec2<int> translate_x(Mat4::T, 0);
    t_mat.set(translate_x, -1.0f);
    mat4_test_case("X-translation by -1 matrix"
      , Mat4::translation(Vec3<float>(-1, 0, 0)), t_mat);

    t_mat.set(translate_x, 0);
    const auto scaling_mat = Mat4::scaling(Vec3<float>(3, 3, 3));
    mat4_test_case("Scaling by 3 matrix", scaling_mat, t_mat *= scaling_mat);

    t_mat = Mat4(1);
    const auto rotation_mat = Mat4::rotation(3.14f / 4, Vec3<int>(0, 1, 1));
    mat4_test_case("Y-Z-rotation by PI/4 matrix", rotation_mat, t_mat *= rotation_mat
      , true, true);
  }

  void Test_units::mat4_test_mutiplications(Mat4& t_mat)
  {
    auto temp(t_mat);
    temp *= 2;
    mat4_test_case("mat * 2", t_mat * 2, temp);

    vec3_f_test_case("mat * vec3f(2.5, 3.4, 4.3)"
      , t_mat * Vec3<float>(2.5f, 3.4f, 4.3f)
      , Vec3<float>(1.77f, 1.99f, 8.6f));

    vec4_f_test_case("mat * vec4f(3.4, 2.5, 5.2, 4.3)"
      , t_mat * Vec4<float>(3.4f, 2.5f, 5.2f, 4.3f)
      , Vec4<float>(2.41f, 1.46f, 10.4f, 4.3f));

    mat4_test_case("mat * Identity", t_mat * Mat4::identity(), t_mat, true, true);
  }

  void Test_units::vec3_f_test_case(const std::string& t_operator
    , const Vec3<float>& t_actual, const Vec3<float>& t_expected)
  {
    const auto EXPECTED("Vec3f(" + Demo_center::double_points_string(t_expected.x)
      + "," + Demo_center::double_points_string(t_expected.y)
      + "," + Demo_center::double_points_string(t_expected.z) + ")");

    const auto CONDITION = abs(t_actual.x - t_expected.x) <= Demo_center::PRECISION
      && abs(t_actual.y - t_expected.y) <= Demo_center::PRECISION
      && abs(t_actual.z - t_expected.z) <= Demo_center::PRECISION;
    show_test_case(t_operator, EXPECTED, CONDITION);

    puts("");
  }

  void Test_units::vec4_f_test_case(const std::string& t_operator, const Vec4<float>& t_actual,
    const Vec4<float>& t_expected)
  {
    const auto EXPECTED("Vec4f(" + Demo_center::double_points_string(t_expected.x)
      + "," + Demo_center::double_points_string(t_expected.y)
      + "," + Demo_center::double_points_string(t_expected.z)
      + "," + Demo_center::double_points_string(t_expected.t) + ")");

    const auto CONDITION = abs(t_actual.x - t_expected.x) <= Demo_center::PRECISION
      && abs(t_actual.y - t_expected.y) <= Demo_center::PRECISION
      && abs(t_actual.z - t_expected.z) <= Demo_center::PRECISION
      && abs(t_actual.t - t_expected.t) <= Demo_center::PRECISION;
    show_test_case(t_operator, EXPECTED, CONDITION);

    puts("");
  }

}//G6037599