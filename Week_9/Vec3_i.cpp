#include "stdafx.h"
#include "Vec3_i.hpp"
#include "Demo_Center/Demo_Center.hpp"

namespace G6037599
{
  //___ static ________________________________________________________
  const Vec3_i Vec3_i::ZEROS = { 0, 0, 0 };
  const Vec3_i Vec3_i::ONES = { 1, 1, 1 };
  const Vec3_i Vec3_i::UP = { 0, 1, 0 };

  void Vec3_i::test_unit()
  {
    test_case("A vector of ones", ONES, Vec3_i(1, 1, 1));
    test_case("A vector of zeros", ZEROS, Vec3_i(0, 0, 0));
    test_case("Up vector", UP, Vec3_i(0, 1, 0));
    Demo_center::press_to_continue();

    Vec3_i v1(0, 9, 0);
    auto v2(v1);
    test_copy_n_assign(v1, v2);
    test_basic_operators(v1, v2);
    test_vector_operators(v1, v2);
    test_other_operators(v1, v2);
  }

  //___ (de)constructors/operators ____________________________________
  Vec3_i::Vec3_i() : x(0), y(0), z(0) {}

  Vec3_i::Vec3_i(const int t_x, const int t_y, const int t_z) 
    : x(t_x), y(t_y), z(t_z) {}

  Vec3_i Vec3_i::operator+=(const Vec3_i& t_other)
  {
    return { x += t_other.x, y += t_other.y, z += t_other.z };
  }

  Vec3_i Vec3_i::operator-=(const Vec3_i& t_other)
  {
    return { x -= t_other.x, y -= t_other.y, z -= t_other.z };
  }

  Vec3_i Vec3_i::operator*=(const int t_scalar)
  {
    return { x *= t_scalar, y *= t_scalar, z *= t_scalar };
  }

  Vec3_i Vec3_i::operator/=(const int t_scalar)
  {
    REQUIRE(t_scalar != 0);
    return { x /= t_scalar, y /= t_scalar, z /= t_scalar };
  }

  Vec3_i Vec3_i::operator<<(const Vec3_i& t_other) const
  {
    return { x << t_other.x, y << t_other.y, z << t_other.z };
  }

  Vec3_i Vec3_i::operator+(const Vec3_i& t_other) const
  {
    return { x + t_other.x, y + t_other.y, z + t_other.z };
  }

  Vec3_i Vec3_i::operator-(const Vec3_i& t_other) const
  {
    return { x - t_other.x, y - t_other.y, z - t_other.z };
  }

  Vec3_i Vec3_i::operator*(const int t_scalar) const
  {
    return { x * t_scalar, y * t_scalar, z * t_scalar };
  }

  Vec3_i Vec3_i::operator/(const int t_scalar) const
  {
    REQUIRE(t_scalar != 0);
    return { x / t_scalar, y / t_scalar, z / t_scalar };
  }

  bool Vec3_i::operator<=(const Vec3_i& t_other) const
  {
    return x <= t_other.x && y <= t_other.y && z <= t_other.z;
  }

  bool Vec3_i::operator>=(const Vec3_i& t_other) const
  {
    return x >= t_other.x && y >= t_other.y && z >= t_other.z;
  }

  bool Vec3_i::operator==(const Vec3_i& t_other) const
  {
    return x == t_other.x && y == t_other.y && z == t_other.z;
  }

  bool Vec3_i::operator!=(const Vec3_i& t_other) const
  {
    return x != t_other.x && y != t_other.y && z != t_other.z;
  }

  bool Vec3_i::operator<(const Vec3_i& t_other) const
  {
    return x < t_other.x && y < t_other.y && z < t_other.z;
  }

  bool Vec3_i::operator>(const Vec3_i& t_other) const
  {
    return x > t_other.x && y > t_other.y && z > t_other.z;
  }

  //___ public _______________________________________________________
  std::string Vec3_i::to_string() const
  {
    return '(' + std::to_string(x) + ',' + std::to_string(y) + ',' 
      + std::to_string(z) + ')';
  }

  int Vec3_i::dot(const Vec3_i& t_other) const
  {
    return x * t_other.x + y * t_other.y + z * t_other.z;
  }

  Vec3_i Vec3_i::cross(const Vec3_i& t_other) const
  {
    return { y * t_other.z - z * t_other.y, z * t_other.x - x * t_other.z
      , x * t_other.y - y * t_other.x };
  }

  int Vec3_i::cross(const Vec3_i& t_v2, const Vec3_i& t_v3) const
  {
    return cross(t_v2).dot(t_v3);
  }

  double Vec3_i::squared_size() const
  {
    return x * x + y * y + z * z;
  }

  void Vec3_i::normalize()
  {
    REQUIRE(size() != 0);
    *this /= static_cast<int>(round(size()));
  }

  Vec3_i Vec3_i::radian_angles() const
  {
    REQUIRE(x != 0); 
    REQUIRE(size() != 0);

    const auto THETA = atan(y / x), P = acos(z / size())
      , ANGLE_X = round(size()*sin(P)*cos(THETA))
      , ANGLE_Y = round(size()*sin(P)*sin(THETA))
      , ANGLE_Z = round(size()*cos(P));
    
    return { static_cast<int>(ANGLE_X), static_cast<int>(ANGLE_Y)
      , static_cast<int>(ANGLE_Z) };
  }

  double Vec3_i::radian_angle_to(const Vec3_i& t_other) const
  {
    REQUIRE(size() != 0); 
    REQUIRE(t_other.size() != 0);

    return acos(dot(t_other) / (size() * t_other.size()));
  }

  //___ private static __________________________________________________
  void Vec3_i::test_case(const std::string& t_operator, const Vec3_i& t_actual
    , const Vec3_i& t_expected)
  {
    Demo_center::show_test_case(t_operator, "Vec3_i" + t_expected.to_string()
      , t_actual == t_expected);
  }

  void Vec3_i::test_copy_n_assign(const Vec3_i& t_v1, Vec3_i& t_v2)
  {
    show("v1", t_v1);
    test_case("auto v2(v1)", t_v2, t_v1);
    const Vec3_i COPY_ASSIGN(4, 5, 7);
    test_case("( v2 = Vec3_i(4, 5, 7) )", t_v2 = COPY_ASSIGN, COPY_ASSIGN);
    Demo_center::press_to_continue();
  }

  void Vec3_i::test_basic_operators(const Vec3_i& t_v1, const Vec3_i& t_v2)
  {
    show(t_v1, t_v2);//0, 9, 0; 4, 5, 7
    test_case("v1 + v2", t_v1 + t_v2, Vec3_i(4, 14, 7));
    test_case("v1 - v2", t_v1 - t_v2, Vec3_i(-4, 4, -7));
    test_case("v1 * 2", t_v1 * 2, Vec3_i(0, 18, 0));
    test_case("v1 / 2", t_v1 / 2, Vec3_i(0, 4, 0));
    Demo_center::press_to_continue();
  }

  void Vec3_i::test_vector_operators(Vec3_i& t_v1, const Vec3_i& t_v2)
  {
    Demo_center::test_case("v1 dot v2", t_v1.dot(t_v2), 45);
    test_case("v1 cross v2", t_v1.cross(t_v2), Vec3_i(63, 0, -36));
    Demo_center::press_to_continue();

    const Vec3_i V3(2, 4, 6);
    show("v3", V3);
    Demo_center::test_case("v1 cross v2, v3", t_v1.cross(t_v2, V3), -90);
    Demo_center::press_to_continue();

    test_sizes_n_normalize(t_v1, 9.0, 81.0);
    test_case("Normalized v1", t_v1, Vec3_i(0, 1, 0));
    Demo_center::press_to_continue();

    test_case("Direction of v2", t_v2.radian_angles(), Vec3_i(5, 5, 7));
    Demo_center::test_case("v1.radian_angle_to(v2)", t_v1.radian_angle_to(t_v2), 1.02);
    Demo_center::press_to_continue();
  }

  void Vec3_i::test_other_operators(Vec3_i& t_v1, Vec3_i& t_v2)
  {
    show(t_v1, t_v2);//0, 1, 0; 4, 5, 7
    test_case("v1 << v2", t_v1 << t_v2, Vec3_i(0, 32, 0));
    Demo_center::press_to_continue();

    test_boolean_operators(t_v1, t_v2);

    test_case("(v2 /= 2)", t_v2 /= 2, Vec3_i(2, 2, 3));
    test_case("(v2 *= 5)", t_v2 *= 5, Vec3_i(10, 10, 15));
    test_case("(v1 += v2)", t_v1 += t_v2, Vec3_i(10, 11, 15));
    test_case("(v2 -= v1)", t_v2 -= t_v1, Vec3_i(0, -1, 0));
  }

  void Vec3_i::test_boolean_operators(const Vec3_i& t_v1, const Vec3_i& t_v2)
  {
    Demo_center::test_case("(v1 <= v2)", t_v1 <= t_v2, true);
    Demo_center::test_case("(v1 >= v2)", t_v1 >= t_v2, false);
    Demo_center::test_case("(v1 != v2)", t_v1 != t_v2, true);
    Demo_center::test_case("(v1 < v2)", t_v1 < t_v2, true);
    Demo_center::test_case("(v1 > v2)", t_v1 > t_v2, false);
    Demo_center::press_to_continue();
  }

}//G6037599