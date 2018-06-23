#include "stdafx.h"
#include "Vec2_i.hpp"
#include "Demo_Center/Demo_Center.hpp"

namespace G6037599
{
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
}//G6037599