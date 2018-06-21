#include "stdafx.h"
#include "Vec2_i.hpp"
#include "Demo_Center/Demo_Center.hpp"

namespace G6037599
{
  //___ non-member static _______________________________________________________
  void test_case(const std::string& t_operator, const Vec2_i& t_actual, const Vec2_i& t_expected);
  void test_case(const std::string& t_operator, double t_actual, double t_expected);
  void test_case(const std::string& t_operator, int t_actual, int t_expected);
  void test_case(const std::string& t_operator, bool t_actual, bool t_expected);
  void show_test_case(const std::string& t_operator, const std::string& t_expected, bool t_condition);
  void press_to_continue();

  void vec2_i_test_unit()
  {
    puts("======================== Vector 2 int Test Unit ==========================");
    puts("");
    test_case("A vector of ones", Vec2_i::ONES, Vec2_i(1, 1));
    test_case("A vector of zeros", Vec2_i::ZEROS, Vec2_i(0, 0));
    press_to_continue();

    Vec2_i v1(0, 9);
    std::cout << " --------- v1: " << v1.to_string() << " --------" << std::endl
      << std::endl;
    auto v2(v1);
    test_case("auto v2(v1)", v2, v1);
    const Vec2_i COPY_ASSIGN(4, 5);
    test_case("( v2 = Vec2_i(4, 5) )", v2 = COPY_ASSIGN, COPY_ASSIGN);
    press_to_continue();

    std::cout << " --------- v1: " << v1.to_string()//0, 9
      << ", v2: " << v2.to_string() << " --------" << std::endl//4, 5
      << std::endl;
    test_case("v1 + v2", v1 + v2, Vec2_i(4, 14));
    test_case("v1 - v2", v1 - v2, Vec2_i(-4, 4));
    test_case("v1 * 2", v1 * 2, Vec2_i(0, 18));
    test_case("v1 / 2", v1 / 2, Vec2_i(0, 4));
    press_to_continue();

    test_case("v1 dot v2", v1.dot(v2), 45);
    test_case("v1 cross v2", v1.cross(v2), -36);
    press_to_continue();

    test_case("Size of v1", v1.size(), 9.0);
    test_case("Size of v1 square", v1.squared_size(), 81.0);
    v1.normalize();
    test_case("Normalized v1", v1, Vec2_i(0, 1));
    press_to_continue();

    test_case("Direction of v2", v2.radian_angle(), 0.79);
    test_case("v1.radian_angle_to(v2)", v1.radian_angle_to(v2), 0.67);
    press_to_continue();

    std::cout << " --------- v1: " << v1.to_string()//0, 1
      << ", v2: " << v2.to_string() << " --------" << std::endl//4, 5
      << std::endl;
    test_case("v1 << v2", v1 << v2, Vec2_i(0, 32));
    press_to_continue();

    test_case("(v1 <= v2)", v1 <= v2, true);
    test_case("(v1 >= v2)", v1 >= v2, false);
    test_case("(v1 != v2)", v1 != v2, true);
    test_case("(v1 < v2)", v1 < v2, true);
    test_case("(v1 > v2)", v1 > v2, false);
    press_to_continue();

    test_case("(v2 /= 2)", v2 /= 2, Vec2_i(2, 2));
    test_case("(v1 *= 5)", v1 *= 5, Vec2_i(0, 5));
    test_case("(v1 += v2)", v1 += v2, Vec2_i(2, 7));
    test_case("(v2 -= v1)", v2 -= v1, Vec2_i(0, -5));
  }

  void test_case(const std::string& t_operator, const Vec2_i& t_actual
    , const Vec2_i& t_expected)
  {
    show_test_case(t_operator, "Vec2_i" + t_expected.to_string()
      , t_actual == t_expected);
  }

  void test_case(const std::string& t_operator, const int t_actual
    , const int t_expected)
  {
    show_test_case(t_operator, std::to_string(t_expected)
      , t_actual == t_expected);
  }

  void test_case(const std::string& t_operator, const double t_actual
    , const double t_expected)
  {
    std::stringstream double_2_decimal_points;
    double_2_decimal_points << std::fixed << std::setprecision(2) 
      << t_expected;
    const auto PRECISION = 0.01;
    show_test_case(t_operator, double_2_decimal_points.str()
      , abs(t_actual - t_expected) <= PRECISION);
  }

  void test_case(const std::string& t_operator, const bool t_actual
    , const bool t_expected)
  {
    show_test_case(t_operator, t_expected? "true": "false"
        , t_actual == t_expected);
  }

  void show_test_case(const std::string& t_operator
    , const std::string& t_expected, const bool t_condition)
  {
    std::cout << "  " << t_operator.c_str() << " == " << t_expected.c_str()
      << " ?: " << (t_condition ? "Pass" : "Fail") 
      << '.' << std::endl;
  }

  void press_to_continue()
  {
    puts("");
    const std::string HINT("Press <Any key> to continue: ");
    std::cout << HINT.c_str();
    Demo_center::wait_key();
    std::cout << '\r' << std::setw(HINT.size()) << std::setfill(' ') 
      << ' ' << '\r';
  }

  //___ member public static __________________________________________
  const Vec2_i Vec2_i::ZEROS = { 0, 0 };
  const Vec2_i Vec2_i::ONES = { 1, 1 };

  //___ (de)constructors/operators ____________________________________
  Vec2_i::Vec2_i(const int t_x, const int t_y) : x(t_x), y(t_y) {}

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

  int Vec2_i::dot(const Vec2_i& t_other) const
  {
    return x*t_other.x + y*t_other.y;
  }

  int Vec2_i::cross(const Vec2_i& t_other) const
  {
    return x * t_other.y - y * t_other.x;
  }

  double Vec2_i::size() const
  {
    return std::sqrt(squared_size());
  }

  double Vec2_i::squared_size() const
  {
    return x * x + y * y;
  }

  Vec2_i Vec2_i::normalize()
  {
    return *this /= static_cast<int>( round( size() ) );
  }

  double Vec2_i::radian_angle() const
  {
    return atan(y/x);
  }

  double Vec2_i::radian_angle_to(const Vec2_i& t_other) const
  {
    return acos(dot(t_other) / (this->size() * t_other.size()));
  }
}//G6037599