#include "stdafx.h"
#include "Vec2_i.hpp"

namespace G6037599
{
  //___ static _______________________________________________________
  void vec2_i_demo()
  {
    const Vec2_i v1(0, 9);
    const Vec2_i v2(4, 5);

    print(v1);
    print(v2);

    if(v1 - v2 == Vec2_i(-4, 4))
    {
      puts("Pass");
    }
  }

  void print(const Vec2_i& t_vector)
  {
    std::cout << '(' << t_vector.x << ',' << t_vector.y << ')' << std::endl;
  }

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

  Vec2_i Vec2_i::operator*=(const Vec2_i& t_other)
  {
    return { x *= t_other.x, y *= t_other.y };
  }

  Vec2_i Vec2_i::operator/=(const Vec2_i& t_other)
  {
    return { x /= t_other.x, y /= t_other.y };
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

  Vec2_i Vec2_i::operator*(const Vec2_i& t_other) const
  {
    return { x * t_other.x, y * t_other.y };
  }

  Vec2_i Vec2_i::operator/(const Vec2_i& t_other) const
  {
    return { x / t_other.x, y / t_other.y };
  }

  Vec2_i Vec2_i::operator*(const float t_scalar) const
  {
    return { x * t_scalar, y * t_scalar };
  }

  Vec2_i Vec2_i::operator/(const float t_scalar) const
  {
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
  int Vec2_i::dot_product(const Vec2_i& t_other) const
  {
    return x*t_other.x + y*t_other.y;
  }

  Vec2_i Vec2_i::closs_product(const Vec2_i& t_other) const
  {
    return Vec2_i{ y - t_other.y, x - t_other.x };
  }

  int Vec2_i::get_magnitude() const
  {
    return sqrt(x*x + y*y);
  }

}//G6037599