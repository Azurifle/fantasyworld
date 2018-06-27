#include "stdafx.h"
#include "Mat4.hpp"

namespace G6037599
{
  // ___ constructor __________________________________________________________
  Mat4::Mat4(const float t_all_value)
  {
    for (auto& row : m_matrix_)
    {
      assign_all_cols(row, t_all_value);
    }
  }

  std::string Mat4::to_string() const
  {
    std::string str;
    for (auto& row : m_matrix_)
    {
      for (auto& col : row)
      {
        str += ' '+std::to_string(col);
      }
      str += '\n';
    }
    
    return str;
  }

  // ___ private static ________________________________________________________
  void Mat4::assign_all_cols(float(&t_row)[SIZE], const float t_all_value)
  {
    for (auto& col : t_row)
    {
      col = t_all_value;
    }
  }
}//G6037599