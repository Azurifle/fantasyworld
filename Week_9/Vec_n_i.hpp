#ifndef G6037599_VEC_N_I_HPP
#define G6037599_VEC_N_I_HPP
#pragma once

namespace G6037599
{
  class Vec_n_i
  {
  public:
    static void test_units();

    static void show(const char* t_name, const Vec_n_i& t_vec_i);
    static void show(const Vec_n_i& t_v1, const Vec_n_i& t_v2);
    static void test_sizes_n_normalize(Vec_n_i& t_v1, double t_size, double t_squared_size);

    Vec_n_i() = default;
    virtual ~Vec_n_i() = default;
    Vec_n_i(const Vec_n_i& t_to_copy) = default;
    Vec_n_i(Vec_n_i&& t_to_move) noexcept = default;
    Vec_n_i& operator = (const Vec_n_i& t_to_copy) = default;
    Vec_n_i& operator = (Vec_n_i&& t_to_move) noexcept = default;

    virtual std::string to_string() const = 0;
    virtual double squared_size() const = 0;
    virtual void normalize() = 0;

    double size() const;
  private:
    static void show_header(int t_vector_type);
  };
}//G6037599

#endif //G6037599_VEC_N_I_HPP