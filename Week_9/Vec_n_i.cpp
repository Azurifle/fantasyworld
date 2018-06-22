#include "stdafx.h"
#include "Vec_n_i.hpp"
#include "Vec3_i.hpp"
#include "Vec2_i.hpp"
#include "Demo_Center/Demo_Center.hpp"

namespace G6037599
{
  //___ static _____________________________________________________________
  void Vec_n_i::test_units()
  {
    show_header(2);
    Vec2_i::test_unit();
    Demo_center::press_to_continue();

    show_header(3);
    Vec3_i::test_unit();
  }

  void Vec_n_i::show(const char* t_name, const Vec_n_i& t_vec_i)
  {
    std::cout << " --------- " << t_name << ": " << t_vec_i.to_string()
      << " --------" << std::endl << std::endl;
  }

  void Vec_n_i::show(const Vec_n_i& t_v1, const Vec_n_i& t_v2)
  {
    std::cout << " --------- v1: " << t_v1.to_string()
      << ", v2: " << t_v2.to_string() << " --------" << std::endl
      << std::endl;
  }

  void Vec_n_i::test_sizes_n_normalize(Vec_n_i& t_v1, const double t_size
    , const double t_squared_size)
  {
    Demo_center::test_case("Size of v1", t_v1.size(), t_size);
    Demo_center::test_case("Size of v1 square", t_v1.squared_size(), t_squared_size);
    t_v1.normalize();
  }

  //___ public _______________________________________________________
  double Vec_n_i::size() const
  {
    return std::sqrt(squared_size());
  }

  //___ private static ______________________________________________________
  void Vec_n_i::show_header(const int t_vector_type)
  {
    std::cout << "======================== Vector " << t_vector_type
      << " int Test Unit ==========================" << std::endl
      << std::endl;
  }
}//G6037599