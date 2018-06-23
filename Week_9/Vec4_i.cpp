#include "stdafx.h"
#include "Vec4_i.hpp"
#include "Demo_Center/Demo_Center.hpp"

namespace G6037599
{
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

}//G6037599