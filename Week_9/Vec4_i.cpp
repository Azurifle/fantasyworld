#include "stdafx.h"
#include "Vec4_i.hpp"
#include "Demo_Center/Demo_Center.hpp"

namespace G6037599
{
  //___ static ________________________________________________________
  void Vec4_i::test_unit()
  {
    test_case("A vector of ones", Vec4_i(ONES), Vec4_i(1, 1, 1, 1));
    test_case("A vector of zeros", Vec4_i(), Vec4_i(0, 0, 0, 0));
    test_case("Up vector", Vec4_i(UP), Vec4_i(0, 1, 0, 0));
    Demo_center::press_to_continue();

    Vec4_i v1(0, 9, 0, 0);
    auto v2(v1);
    test_copy_n_assign(v1, v2);
    test_basic_operators(v1, v2);
    test_vector_operators(v1, v2);
    test_other_operators(v1, v2);
  }

  //___ (de)constructors/operators ____________________________________
  Vec4_i::Vec4_i(const Type t_typ) : x(t_typ), y(t_typ), z(t_typ), t(t_typ)
  {
    switch (t_typ)
    {
    case UP: x = 0; y = 1; z = 0, t = 0; default:;
    }
  }

  Vec4_i::Vec4_i(const int t_x, const int t_y, const int t_z, const int t_t)
    : x(t_x), y(t_y), z(t_z), t(t_t) {}

  Vec4_i Vec4_i::operator+=(const Vec4_i& t_other)
  {
    return { x += t_other.x, y += t_other.y, z += t_other.z, t += t_other.t };
  }

  Vec4_i Vec4_i::operator-=(const Vec4_i& t_other)
  {
    return { x -= t_other.x, y -= t_other.y, z -= t_other.z, t -= t_other.t };
  }

  Vec4_i Vec4_i::operator*=(const int t_scalar)
  {
    return { x *= t_scalar, y *= t_scalar, z *= t_scalar, t *= t_scalar };
  }

  Vec4_i Vec4_i::operator/=(const int t_scalar)
  {
    REQUIRE(t_scalar != 0);
    return { x /= t_scalar, y /= t_scalar, z /= t_scalar, t /= t_scalar };
  }

  Vec4_i Vec4_i::operator<<(const Vec4_i& t_other) const
  {
    return { x << t_other.x, y << t_other.y, z << t_other.z, t << t_other.t };
  }

  Vec4_i Vec4_i::operator+(const Vec4_i& t_other) const
  {
    return { x + t_other.x, y + t_other.y, z + t_other.z, t + t_other.t };
  }

  Vec4_i Vec4_i::operator-(const Vec4_i& t_other) const
  {
    return { x - t_other.x, y - t_other.y, z - t_other.z, t - t_other.t };
  }

  Vec4_i Vec4_i::operator*(const int t_scalar) const
  {
    return { x * t_scalar, y * t_scalar, z * t_scalar, t * t_scalar };
  }

  Vec4_i Vec4_i::operator/(const int t_scalar) const
  {
    REQUIRE(t_scalar != 0);
    return { x / t_scalar, y / t_scalar, z / t_scalar, t / t_scalar };
  }

  bool Vec4_i::operator<=(const Vec4_i& t_other) const
  {
    return x <= t_other.x && y <= t_other.y && z <= t_other.z;
  }

  bool Vec4_i::operator>=(const Vec4_i& t_other) const
  {
    return x >= t_other.x && y >= t_other.y && z >= t_other.z 
      && t >= t_other.t;
  }

  bool Vec4_i::operator==(const Vec4_i& t_other) const
  {
    return x == t_other.x && y == t_other.y && z == t_other.z
      && t == t_other.t;
  }

  bool Vec4_i::operator!=(const Vec4_i& t_other) const
  {
    return x != t_other.x && y != t_other.y && z != t_other.z
      && t != t_other.t;
  }

  bool Vec4_i::operator<(const Vec4_i& t_other) const
  {
    return x < t_other.x && y < t_other.y && z < t_other.z
      && t < t_other.t;
  }

  bool Vec4_i::operator>(const Vec4_i& t_other) const
  {
    return x > t_other.x && y > t_other.y && z > t_other.z
      && t > t_other.t;
  }

  //___ public _______________________________________________________
  std::string Vec4_i::to_string() const
  {
    return '(' + std::to_string(x) + ',' + std::to_string(y) + ',' 
      + std::to_string(z) + ',' + std::to_string(t) + ')';
  }

  int Vec4_i::dot(const Vec4_i& t_other) const
  {
    return x * t_other.x + y * t_other.y + z * t_other.z + t * t_other.t;
  }

  double Vec4_i::squared_size() const
  {
    return x * x + y * y + z * z + t * t;
  }

  void Vec4_i::normalize()
  {
    REQUIRE(size() != 0);
    *this /= static_cast<int>(round(size()));
  }

  double Vec4_i::radian_angle_to(const Vec4_i& t_other) const
  {
    REQUIRE(size() != 0); 
    REQUIRE(t_other.size() != 0);

    return acos(dot(t_other) / (size() * t_other.size()));
  }

  //___ private static __________________________________________________
  void Vec4_i::test_case(const std::string& t_operator, const Vec4_i& t_actual
    , const Vec4_i& t_expected)
  {
    Demo_center::show_test_case(t_operator, "Vec4_i" + t_expected.to_string()
      , t_actual == t_expected);
  }

  void Vec4_i::test_copy_n_assign(const Vec4_i& t_v1, Vec4_i& t_v2)
  {
    show("v1", t_v1);
    test_case("auto v2(v1)", t_v2, t_v1);
    const Vec4_i COPY_ASSIGN(4, 5, 7, -10);
    test_case("( v2 = Vec4_i(4, 5, 7, -10) )", t_v2 = COPY_ASSIGN, COPY_ASSIGN);
    Demo_center::press_to_continue();
  }

  void Vec4_i::test_basic_operators(const Vec4_i& t_v1, const Vec4_i& t_v2)
  {
    show(t_v1, t_v2);//0, 9, 0, 0; 4, 5, 7, -10
    test_case("v1 + v2", t_v1 + t_v2, Vec4_i(4, 14, 7, -10));
    test_case("v1 - v2", t_v1 - t_v2, Vec4_i(-4, 4, -7, 10));
    test_case("v1 * 2", t_v1 * 2, Vec4_i(0, 18, 0, 0));
    test_case("v1 / 2", t_v1 / 2, Vec4_i(0, 4, 0, 0));
    Demo_center::press_to_continue();
  }

  void Vec4_i::test_vector_operators(Vec4_i& t_v1, const Vec4_i& t_v2)
  {
    Demo_center::test_case("v1 dot v2", t_v1.dot(t_v2), 45);
    puts("");
    puts(" ____ Cross product issue for vector 4D (Need vector 6D) ____________________");
    puts("| https://www.gamedev.net/forums/topic/289972-cross-product-of-2d-vectors/   |");
    puts("| https://math.stackexchange.com/questions/424482/cross-product-in-mathbb-rn |");
    puts("|____________________________________________________________________________|");
    Demo_center::press_to_continue();

    test_sizes_n_normalize(t_v1, 9.0, 81.0);
    test_case("Normalized v1", t_v1, Vec4_i(0, 1, 0, 0));
    Demo_center::press_to_continue();

    puts(" ____ Need vector 6D to represent 6 euler angles ____________________________");
    puts("| https://www.gamedev.net/forums/topic/83265-4d-rotation/                    |");
    puts("|____________________________________________________________________________|");
    puts("");
    Demo_center::test_case("v1.radian_angle_to(v2)", t_v1.radian_angle_to(t_v2), 1.2);
    Demo_center::press_to_continue();
  }

  void Vec4_i::test_other_operators(Vec4_i& t_v1, Vec4_i& t_v2)
  {
    show(t_v1, t_v2);//0, 1, 0, 0; 4, 5, 7, -10
    test_case("v1 << v2", t_v1 << t_v2, Vec4_i(0, 32, 0, 0));
    Demo_center::press_to_continue();

    test_boolean_operators(t_v1, t_v2);

    test_case("(v2 /= 2)", t_v2 /= 2, Vec4_i(2, 2, 3, -5));
    test_case("(v2 *= 5)", t_v2 *= 5, Vec4_i(10, 10, 15, -25));
    test_case("(v1 += v2)", t_v1 += t_v2, Vec4_i(10, 11, 15, -25));
    test_case("(v2 -= v1)", t_v2 -= t_v1, Vec4_i(0, -1, 0, 0));
  }

  void Vec4_i::test_boolean_operators(const Vec4_i& t_v1, const Vec4_i& t_v2)
  {
    Demo_center::test_case("(v1 <= v2)", t_v1 <= t_v2, true);
    Demo_center::test_case("(v1 >= v2)", t_v1 >= t_v2, false);
    Demo_center::test_case("(v1 != v2)", t_v1 != t_v2, true);
    Demo_center::test_case("(v1 < v2)", t_v1 < t_v2, false);
    Demo_center::test_case("(v1 > v2)", t_v1 > t_v2, false);
    Demo_center::press_to_continue();
  }

}//G6037599