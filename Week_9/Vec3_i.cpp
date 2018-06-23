#include "stdafx.h"
#include "Vec3_i.hpp"
#include "Demo_Center/Demo_Center.hpp"

namespace G6037599
{
  //___ (de)constructors/operators ____________________________________
  Vec3_i::Vec3_i(const Type t_typ) : x(t_typ), y(t_typ), z(t_typ)
  {
    switch (t_typ)
    {
    case UP: x = 0; y = 1; z = 0; default:;
    }
  }

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

}//G6037599