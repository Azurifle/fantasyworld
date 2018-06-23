#include "stdafx.h"
#include "Vec2_i.hpp"
#include "Demo_Center/Demo_Center.hpp"

namespace G6037599
{
  //___ static ________________________________________________________
  void Vec2_i::test_unit()
  {
    test_case("A vector of ones", Vec2_i(ONES), Vec2_i(1, 1));
    test_case("A vector of zeros", Vec2_i(), Vec2_i(0, 0));
    Demo_center::press_to_continue();

    Vec2_i v1(0, 9);
    auto v2(v1);
    test_copy_n_assign(v1, v2);
    test_basic_operators(v1, v2);
    test_vector_operators(v1, v2);
    test_other_operators(v1, v2);
  }

  //___ (de)constructors/operators ____________________________________
  Vec2_i::Vec2_i(const Type t_typ): x(t_typ), y(t_typ) {}

  Vec2_i::Vec2_i(const int t_x, const int t_y): x(t_x), y(t_y) {}

  Vec2_i Vec2_i::operator+=(const Vec2_i& t_other)
  {
    return { x += t_other.x, y += t_other.y };
  }

  Vec2_i Vec2_i::operator-=(const Vec2_i& t_other)
  {
    return { x -= t_other.x, y -= t_other.y };
  }

  Vec2_i Vec2_i::operator*=(const int t_scalar)
  {
    return { x *= t_scalar, y *= t_scalar };
  }

  Vec2_i Vec2_i::operator/=(const int t_scalar)
  {
    REQUIRE(t_scalar != 0);
    return { x /= t_scalar, y /= t_scalar };
  }

  Vec2_i Vec2_i::operator<<(const Vec2_i& t_other) const
  {
    return { x << t_other.x, y << t_other.y };
  }

  Vec2_i Vec2_i::operator+(const Vec2_i& t_other) const
  {
    return { x + t_other.x, y + t_other.y };
  }

  Vec2_i Vec2_i::operator-(const Vec2_i& t_other) const
  {
    return { x - t_other.x, y - t_other.y };
  }

  Vec2_i Vec2_i::operator*(const int t_scalar) const
  {
    return { x * t_scalar, y * t_scalar };
  }

  Vec2_i Vec2_i::operator/(const int t_scalar) const
  {
    REQUIRE(t_scalar != 0);
    return { x / t_scalar, y / t_scalar };
  }

  bool Vec2_i::operator<=(const Vec2_i& t_other) const
  {
    return x <= t_other.x && y <= t_other.y;
  }

  bool Vec2_i::operator>=(const Vec2_i& t_other) const
  {
    return x >= t_other.x && y >= t_other.y;
  }

  bool Vec2_i::operator==(const Vec2_i& t_other) const
  {
    return x == t_other.x && y == t_other.y;
  }

  bool Vec2_i::operator!=(const Vec2_i& t_other) const
  {
    return x != t_other.x && y != t_other.y;
  }

  bool Vec2_i::operator<(const Vec2_i& t_other) const
  {
    return x < t_other.x && y < t_other.y;
  }

  bool Vec2_i::operator>(const Vec2_i& t_other) const
  {
    return x > t_other.x && y > t_other.y;
  }

  //___ public _______________________________________________________
  std::string Vec2_i::to_string() const
  {
    return '(' + std::to_string(x) + ',' + std::to_string(y) + ')';
  }

  double Vec2_i::squared_size() const
  {
    return x * x + y * y;
  }

  void Vec2_i::normalize()
  {
    REQUIRE(size() != 0);
    *this /= static_cast<int>(round(size()));
  }

  int Vec2_i::dot(const Vec2_i& t_other) const
  {
    return x*t_other.x + y*t_other.y;
  }

  int Vec2_i::cross(const Vec2_i& t_other) const
  {
    return x * t_other.y - y * t_other.x;
  }

  Vec2_i Vec2_i::get_det() const
  {
    return {y, -x};
  }

  double Vec2_i::radian_angle() const
  {
    REQUIRE(x != 0);
    return atan(y/x);
  }

  double Vec2_i::radian_angle_to(const Vec2_i& t_other) const
  {
    REQUIRE(size() != 0); REQUIRE(t_other.size() != 0);
    return acos(dot(t_other) / (size() * t_other.size()));
  }

  //___ private static __________________________________________________
  void Vec2_i::test_case(const std::string& t_operator, const Vec2_i& t_actual
    , const Vec2_i& t_expected)
  {
    Demo_center::show_test_case(t_operator, "Vec2_i" + t_expected.to_string()
      , t_actual == t_expected);
  }

  void Vec2_i::test_copy_n_assign(const Vec2_i& t_v1, Vec2_i& t_v2)
  {
    show("v1", t_v1);
    test_case("auto v2(v1)", t_v2, t_v1);
    const Vec2_i COPY_ASSIGN(4, 5);
    test_case("( v2 = Vec3_i(4, 5) )", t_v2 = COPY_ASSIGN, COPY_ASSIGN);
    Demo_center::press_to_continue();
  }

  void Vec2_i::test_basic_operators(const Vec2_i& t_v1, const Vec2_i& t_v2)
  {
    show(t_v1, t_v2);//0, 9; 4, 5
    test_case("v1 + v2", t_v1 + t_v2, Vec2_i(4, 14));
    test_case("v1 - v2", t_v1 - t_v2, Vec2_i(-4, 4));
    test_case("v1 * 2", t_v1 * 2, Vec2_i(0, 18));
    test_case("v1 / 2", t_v1 / 2, Vec2_i(0, 4));
    Demo_center::press_to_continue();
  }

  void Vec2_i::test_vector_operators(Vec2_i& t_v1, const Vec2_i& t_v2)
  {
    Demo_center::test_case("v1 dot v2", t_v1.dot(t_v2), 45);
    Demo_center::test_case("v1 cross v2", t_v1.cross(t_v2), -36);
    test_case("det of v1 ", t_v1.get_det(), Vec2_i(9, 0));
    Demo_center::press_to_continue();

    test_sizes_n_normalize(t_v1, 9.0, 81.0);
    test_case("Normalized v1", t_v1, Vec2_i(0, 1));
    Demo_center::press_to_continue();

    Demo_center::test_case("Direction of v2", t_v2.radian_angle(), 0.79);
    Demo_center::test_case("v1.radian_angle_to(v2)", t_v1.radian_angle_to(t_v2), 0.67);
    Demo_center::press_to_continue();
  }

  void Vec2_i::test_other_operators(Vec2_i& t_v1, Vec2_i& t_v2)
  {
    show(t_v1, t_v2);//0, 1; 4, 5
    test_case("v1 << v2", t_v1 << t_v2, Vec2_i(0, 32));
    Demo_center::press_to_continue();

    test_boolean_operators(t_v1, t_v2);

    test_case("(v2 /= 2)", t_v2 /= 2, Vec2_i(2, 2));
    test_case("(v1 *= 5)", t_v1 *= 5, Vec2_i(0, 5));
    test_case("(v1 += v2)", t_v1 += t_v2, Vec2_i(2, 7));
    test_case("(v2 -= v1)", t_v2 -= t_v1, Vec2_i(0, -5));
  }

  void Vec2_i::test_boolean_operators(const Vec2_i& t_v1, const Vec2_i& t_v2)
  {
    Demo_center::test_case("(v1 <= v2)", t_v1 <= t_v2, true);
    Demo_center::test_case("(v1 >= v2)", t_v1 >= t_v2, false);
    Demo_center::test_case("(v1 != v2)", t_v1 != t_v2, true);
    Demo_center::test_case("(v1 < v2)", t_v1 < t_v2, true);
    Demo_center::test_case("(v1 > v2)", t_v1 > t_v2, false);
    Demo_center::press_to_continue();
  }

}//G6037599