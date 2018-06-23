#ifndef G6037599_VEC_N_I_HPP
#define G6037599_VEC_N_I_HPP
#pragma once

namespace G6037599
{
  class Vec_n
  {
  public:
    Vec_n() = default;
    virtual ~Vec_n() = default;
    Vec_n(const Vec_n& t_to_copy) = default;
    Vec_n(Vec_n&& t_to_move) noexcept = default;
    Vec_n& operator = (const Vec_n& t_to_copy) = default;
    Vec_n& operator = (Vec_n&& t_to_move) noexcept = default;

    virtual std::string to_string() const = 0;
    virtual double squared_size() const = 0;//Faster than size() that use sqrt() for optimization
    virtual void normalize() = 0;

    double size() const;
  };
}//G6037599

#endif //G6037599_VEC_N_I_HPP