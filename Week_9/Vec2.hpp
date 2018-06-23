#ifndef G6037599_VEC2_I_HPP
#define G6037599_VEC2_I_HPP
#pragma once
#include "Vec_n.hpp"

namespace G6037599
{
  template <class T>
  class Vec2 final: public Vec_n
  {
  public:
    T x, y;//if there is no setter constraint make it public

    explicit Vec2(Type t_typ = ZEROS);
    ~Vec2() = default;
    Vec2(T t_x, T t_y);
    Vec2(const Vec2<T>& t_to_copy) = default;
    Vec2(Vec2<T>&& t_to_move) noexcept = default;
    Vec2<T>& operator = (const Vec2<T>& t_to_copy) = default;
    Vec2<T>& operator = (Vec2<T>&& t_to_move) noexcept = default;

    Vec2 operator += (const Vec2<T>& t_other);
    Vec2 operator -= (const Vec2<T>& t_other);
    Vec2 operator *= (T t_scalar);
    Vec2 operator /= (T t_scalar);

    //Vec2 operator << (const Vec2<T>& t_other) const;
    Vec2 operator + (const Vec2<T>& t_other) const;
    Vec2 operator - (const Vec2<T>& t_other) const;
    Vec2 operator * (T t_scalar) const;
    Vec2 operator / (T t_scalar) const;

    bool operator <= (const Vec2<T>& t_other) const;
    bool operator >= (const Vec2<T>& t_other) const;
    bool operator == (const Vec2<T>& t_other) const;
    bool operator != (const Vec2<T>& t_other) const;
    bool operator < (const Vec2<T>& t_other) const;
    bool operator > (const Vec2<T>& t_other) const;

    std::string to_string() const override;
    double squared_size() const override;
    void normalize() override;

    T dot(const Vec2<T>& t_other) const;
    T cross(const Vec2<T>& t_other) const;
    Vec2 get_det() const;
    double radian_angle() const;
    double radian_angle_to(const Vec2<T>& t_other) const;
  };
}//G6037599

#endif //G6037599_VEC2_I_HPP