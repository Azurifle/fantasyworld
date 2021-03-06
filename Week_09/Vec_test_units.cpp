#include "stdafx.h"
#include "Vec_test_units.hpp"
#include "Demo_Center/Demo_Center.hpp"
#include "Demo_Center/Test_units.hpp"

namespace G6037599
{
  //___ static ________________________________________________________
  void Vec_test_units::run()
  {
    show_header(2);
    vec2_test_unit();
    Demo_center::press_to_continue();

    show_header(3);
    vec3_test_unit();
    Demo_center::press_to_continue();

    show_header(4);
    vec4_test_unit();
  }

  //___ private static _______________________________________________
  void Vec_test_units::show_header(const int t_vector_type)
  {
    Demo_center::print_centered_header(std::string("Vector ")
      +std::to_string(t_vector_type)+" int Test Unit", '=');
    puts("");
  }

  void Vec_test_units::show(const char* t_name, const std::string& t_vec)
  {
    std::cout << " --------- " << t_name << ": " << t_vec
      << " --------" << std::endl << std::endl;
  }

  void Vec_test_units::show(const std::string& t_v1, const std::string& t_v2)
  {
    std::cout << " --------- v1: " << t_v1 << ", v2: " << t_v2 
      << " --------" << std::endl << std::endl;
  }

  void Vec_test_units::test_sizes(const double t_size, const double t_squared_size)
  {
    Test_units::test_case("Size of v1", t_size, 9.0);
    Test_units::test_case("Size of v1 square", t_squared_size, 81.0);
  }

  //___ vec2_test_unit _______________________________________________
  void Vec_test_units::vec2_test_unit()
  {
    vec2_test_case("A vector of ones", Vec2<int>(1), Vec2<int>(1, 1));
    vec2_test_case("A vector of zeros", Vec2<int>(), Vec2<int>(0, 0));
    Demo_center::press_to_continue();

    Vec2<int> v1(0, 9);
    auto v2(v1);
    vec2_test_copy(v1, v2);
    vec2_test_basic_operators(v1, v2);
    vec2_test_vector_operators(v1, v2);
    vec2_test_boolean_operators(v1, v2);
    vec2_test_assign_operators(v1, v2);
  }

  void Vec_test_units::vec2_test_case(const std::string& t_operator, const Vec2<int>& t_actual
    , const Vec2<int>& t_expected)
  {
    Test_units::show_test_case(t_operator, "Vec2" + t_expected.to_string()
      , t_actual == t_expected);
  }

  void Vec_test_units::vec2_test_copy(const Vec2<int>& t_v1, Vec2<int>& t_v2)
  {
    show("v1", t_v1.to_string());
    vec2_test_case("auto v2(v1)", t_v2, t_v1);
    const Vec2<int> COPY_ASSIGN(4, 5);
    vec2_test_case("( v2 = Vec2_i(4, 5) )", t_v2 = COPY_ASSIGN, COPY_ASSIGN);
    Demo_center::press_to_continue();
  }

  void Vec_test_units::vec2_test_basic_operators(const Vec2<int>& t_v1, const Vec2<int>& t_v2)
  {
    show(t_v1.to_string(), t_v2.to_string());//0, 9; 4, 5
    vec2_test_case("v1 + v2", t_v1 + t_v2, Vec2<int>(4, 14));
    vec2_test_case("v1 - v2", t_v1 - t_v2, Vec2<int>(-4, 4));
    vec2_test_case("v1 * 2", t_v1 * 2, Vec2<int>(0, 18));
    vec2_test_case("v1 / 2", t_v1 / 2, Vec2<int>(0, 4));
    Demo_center::press_to_continue();
  }

  void Vec_test_units::vec2_test_vector_operators(Vec2<int>& t_v1, const Vec2<int>& t_v2)
  {
    Test_units::test_case("v1 dot v2", t_v1.dot(t_v2), 45);
    Test_units::test_case("v1 cross v2", t_v1.cross(t_v2), -36);
    vec2_test_case("det of v1 ", t_v1.get_det(), Vec2<int>(9, 0));
    Demo_center::press_to_continue();

    test_sizes(t_v1.size(), t_v1.squared_size());
    t_v1.normalize();
    vec2_test_case("Normalized v1", t_v1, Vec2<int>(0, 1));
    Demo_center::press_to_continue();

    Test_units::test_case("Direction of v2", t_v2.radian_angle(), 0.79);
    Test_units::test_case("v1.radian_angle_to(v2)", t_v1.radian_angle_to(t_v2), 0.67);
    Demo_center::press_to_continue();
  }

  void Vec_test_units::vec2_test_boolean_operators(const Vec2<int>& t_v1, const Vec2<int>& t_v2)
  {
    show(t_v1.to_string(), t_v2.to_string());//0, 1; 4, 5
    Test_units::test_case("(v1 <= v2)", t_v1 <= t_v2, true);
    Test_units::test_case("(v1 >= v2)", t_v1 >= t_v2, false);
    Test_units::test_case("(v1 != v2)", t_v1 != t_v2, true);
    Test_units::test_case("(v1 < v2)", t_v1 < t_v2, true);
    Test_units::test_case("(v1 > v2)", t_v1 > t_v2, false);
    Demo_center::press_to_continue();
  }

  void Vec_test_units::vec2_test_assign_operators(Vec2<int>& t_v1, Vec2<int>& t_v2)
  {
    vec2_test_case("(v2 /= 2)", t_v2 /= 2, Vec2<int>(2, 2));
    vec2_test_case("(v1 *= 5)", t_v1 *= 5, Vec2<int>(0, 5));
    vec2_test_case("(v1 += v2)", t_v1 += t_v2, Vec2<int>(2, 7));
    vec2_test_case("(v2 -= v1)", t_v2 -= t_v1, Vec2<int>(0, -5));
  }

  //___ vec3_test_unit _______________________________________________
  void Vec_test_units::vec3_test_unit()
  {
    vec3_test_case("A vector of ones", Vec3<int>(1), Vec3<int>(1, 1, 1));
    vec3_test_case("A vector of zeros", Vec3<int>(), Vec3<int>(0, 0, 0));
    vec3_test_case("Up vector", Vec3<int>::UP, Vec3<int>(0, 1, 0));
    Demo_center::press_to_continue();

    Vec3<int> v1(0, 9, 0);
    auto v2(v1);
    vec3_test_copy(v1, v2);
    vec3_test_basic_operators(v1, v2);
    vec3_test_vector_operators(v1, v2);
    vec3_test_boolean_operators(v1, v2);
    vec3_test_assign_operators(v1, v2);
  }

  void Vec_test_units::vec3_test_case(const std::string& t_operator, const Vec3<int>& t_actual
    , const Vec3<int>& t_expected)
  {
    Test_units::show_test_case(t_operator, "Vec3_i" + t_expected.to_string()
      , t_actual == t_expected);
  }

  void Vec_test_units::vec3_test_copy(const Vec3<int>& t_v1, Vec3<int>& t_v2)
  {
    show("v1", t_v1.to_string());
    vec3_test_case("auto v2(v1)", t_v2, t_v1);
    const Vec3<int> COPY_ASSIGN(4, 5, 7);
    vec3_test_case("( v2 = Vec3_i(4, 5, 7) )", t_v2 = COPY_ASSIGN, COPY_ASSIGN);
    Demo_center::press_to_continue();
  }

  void Vec_test_units::vec3_test_basic_operators(const Vec3<int>& t_v1, const Vec3<int>& t_v2)
  {
    show(t_v1.to_string(), t_v2.to_string());//0, 9, 0; 4, 5, 7
    vec3_test_case("v1 + v2", t_v1 + t_v2, Vec3<int>(4, 14, 7));
    vec3_test_case("v1 - v2", t_v1 - t_v2, Vec3<int>(-4, 4, -7));
    vec3_test_case("v1 * 2", t_v1 * 2, Vec3<int>(0, 18, 0));
    vec3_test_case("v1 / 2", t_v1 / 2, Vec3<int>(0, 4, 0));
    Demo_center::press_to_continue();
  }

  void Vec_test_units::vec3_test_vector_operators(Vec3<int>& t_v1, const Vec3<int>& t_v2)
  {
    Test_units::test_case("v1 dot v2", t_v1.dot(t_v2), 45);
    vec3_test_case("v1 cross v2", t_v1.cross(t_v2), Vec3<int>(63, 0, -36));
    Demo_center::press_to_continue();

    const Vec3<int> V3(2, 4, 6);
    show("v3", V3.to_string());
    Test_units::test_case("v1 cross v2, v3", t_v1.cross(t_v2, V3), -90);
    Demo_center::press_to_continue();

    test_sizes(t_v1.size(), t_v1.squared_size());
    t_v1.normalize();
    vec3_test_case("Normalized v1", t_v1, Vec3<int>(0, 1, 0));
    Demo_center::press_to_continue();

    vec3_test_case("Direction of v2", t_v2.radian_angles(), Vec3<int>(5, 5, 7));
    Test_units::test_case("v1.radian_angle_to(v2)", t_v1.radian_angle_to(t_v2), 1.02);
    Demo_center::press_to_continue();
  }

  void Vec_test_units::vec3_test_boolean_operators(const Vec3<int>& t_v1, const Vec3<int>& t_v2)
  {
    show(t_v1.to_string(), t_v2.to_string());//0, 1, 0; 4, 5, 7
    Test_units::test_case("(v1 <= v2)", t_v1 <= t_v2, true);
    Test_units::test_case("(v1 >= v2)", t_v1 >= t_v2, false);
    Test_units::test_case("(v1 != v2)", t_v1 != t_v2, true);
    Test_units::test_case("(v1 < v2)", t_v1 < t_v2, true);
    Test_units::test_case("(v1 > v2)", t_v1 > t_v2, false);
    Demo_center::press_to_continue();
  }

  void Vec_test_units::vec3_test_assign_operators(Vec3<int>& t_v1, Vec3<int>& t_v2)
  {
    vec3_test_case("(v2 /= 2)", t_v2 /= 2, Vec3<int>(2, 2, 3));
    vec3_test_case("(v2 *= 5)", t_v2 *= 5, Vec3<int>(10, 10, 15));
    vec3_test_case("(v1 += v2)", t_v1 += t_v2, Vec3<int>(10, 11, 15));
    vec3_test_case("(v2 -= v1)", t_v2 -= t_v1, Vec3<int>(0, -1, 0));
  }

  //___ vec4_test_unit _______________________________________________
  void Vec_test_units::vec4_test_unit()
  {
    vec4_test_case("A vector of ones", Vec4<int>(1), Vec4<int>(1, 1, 1, 1));
    vec4_test_case("A vector of zeros", Vec4<int>(), Vec4<int>(0, 0, 0, 0));
    vec4_test_case("Up vector", Vec4<int>::UP, Vec4<int>(0, 1, 0, 0));
    Demo_center::press_to_continue();

    Vec4<int> v1(0, 9, 0, 0);
    auto v2(v1);
    vec4_test_copy(v1, v2);
    vec4_test_basic_operators(v1, v2);
    vec4_test_vector_operators(v1, v2);
    vec4_test_boolean_operators(v1, v2);
    vec4_test_assign_operators(v1, v2);
  }

  void Vec_test_units::vec4_test_case(const std::string& t_operator, const Vec4<int>& t_actual
    , const Vec4<int>& t_expected)
  {
    Test_units::show_test_case(t_operator, "Vec4_i" + t_expected.to_string()
      , t_actual == t_expected);
  }

  void Vec_test_units::vec4_test_copy(const Vec4<int>& t_v1, Vec4<int>& t_v2)
  {
    show("v1", t_v1.to_string());
    vec4_test_case("auto v2(v1)", t_v2, t_v1);
    const Vec4<int> COPY_ASSIGN(4, 5, 7, -10);
    vec4_test_case("( v2 = Vec4_i(4, 5, 7, -10) )", t_v2 = COPY_ASSIGN, COPY_ASSIGN);
    Demo_center::press_to_continue();
  }

  void Vec_test_units::vec4_test_basic_operators(const Vec4<int>& t_v1, const Vec4<int>& t_v2)
  {
    show(t_v1.to_string(), t_v2.to_string());//0, 9, 0, 0; 4, 5, 7, -10
    vec4_test_case("v1 + v2", t_v1 + t_v2, Vec4<int>(4, 14, 7, -10));
    vec4_test_case("v1 - v2", t_v1 - t_v2, Vec4<int>(-4, 4, -7, 10));
    vec4_test_case("v1 * 2", t_v1 * 2, Vec4<int>(0, 18, 0, 0));
    vec4_test_case("v1 / 2", t_v1 / 2, Vec4<int>(0, 4, 0, 0));
    Demo_center::press_to_continue();
  }

  void Vec_test_units::vec4_test_vector_operators(Vec4<int>& t_v1, const Vec4<int>& t_v2)
  {
    Test_units::test_case("v1 dot v2", t_v1.dot(t_v2), 45);
    puts("");
    puts(" ____ Cross product issue for vector 4D (Need vector 6D) ____________________");
    puts("| https://www.gamedev.net/forums/topic/289972-cross-product-of-2d-vectors/   |");
    puts("| https://math.stackexchange.com/questions/424482/cross-product-in-mathbb-rn |");
    puts("|____________________________________________________________________________|");
    Demo_center::press_to_continue();

    test_sizes(t_v1.size(), t_v1.squared_size());
    t_v1.normalize();
    vec4_test_case("Normalized v1", t_v1, Vec4<int>(0, 1, 0, 0));
    Demo_center::press_to_continue();

    puts(" ____ Need vector 6D to represent 6 euler angles ____________________________");
    puts("| https://www.gamedev.net/forums/topic/83265-4d-rotation/                    |");
    puts("|____________________________________________________________________________|");
    puts("");
    Test_units::test_case("v1.radian_angle_to(v2)", t_v1.radian_angle_to(t_v2), 1.2);
    Demo_center::press_to_continue();
  }

  void Vec_test_units::vec4_test_boolean_operators(const Vec4<int>& t_v1, const Vec4<int>& t_v2)
  {
    show(t_v1.to_string(), t_v2.to_string());//0, 1, 0, 0; 4, 5, 7, -10
    Test_units::test_case("(v1 <= v2)", t_v1 <= t_v2, true);
    Test_units::test_case("(v1 >= v2)", t_v1 >= t_v2, false);
    Test_units::test_case("(v1 != v2)", t_v1 != t_v2, true);
    Test_units::test_case("(v1 < v2)", t_v1 < t_v2, false);
    Test_units::test_case("(v1 > v2)", t_v1 > t_v2, false);
    Demo_center::press_to_continue();
  }

  void Vec_test_units::vec4_test_assign_operators(Vec4<int>& t_v1, Vec4<int>& t_v2)
  {
    vec4_test_case("(v2 /= 2)", t_v2 /= 2, Vec4<int>(2, 2, 3, -5));
    vec4_test_case("(v2 *= 5)", t_v2 *= 5, Vec4<int>(10, 10, 15, -25));
    vec4_test_case("(v1 += v2)", t_v1 += t_v2, Vec4<int>(10, 11, 15, -25));
    vec4_test_case("(v2 -= v1)", t_v2 -= t_v1, Vec4<int>(0, -1, 0, 0));
  }

}//G6037599