#include "stdafx.h"
#include "Mat4.hpp"
#include "Demo_Center/Demo_Center.hpp"

namespace G6037599
{
  // ___ static _________________________________________________________________
  Mat4 Mat4::identity()
  {
    return Mat4(1);
  }

  Mat4 Mat4::get_translated(const Vec3<float>& t_translate)
  {
    return {};
  }//*****

  Mat4 Mat4::get_rotated(const float t_radian_angle, const Vec3<float>& t_axis)
  {
    return {};
  }//*****

  Mat4 Mat4::get_scaled(const Vec3<float>& t_scale)
  {
    return {};
  }//*****

  Mat4 Mat4::get_transposed(const Mat4& t_matrix)
  {
    return {};
  }//*****

  Mat4 Mat4::inverse(const Mat4& t_matrix)
  {
    return {};
  }//*****

  // ___ constructor __________________________________________________________
  Mat4::Mat4()
  {
    for (auto& row : m_mat_)
    {
      for (auto& col : row)
      {
        col = 0.0f;
      }
    }
  }
  
  Mat4::Mat4(const float t_diagonal)
  {
    for(auto i = 0; i < SIZE; ++i)
    {
      m_mat_[i][i] = t_diagonal;
    }
  }

  Mat4::Mat4(const float(& t_array_2_d)[SIZE][SIZE])
  {
    for (auto row = 0; row < SIZE; ++row)
    {
      for (auto col = 0; col < SIZE; ++col)
      {
        m_mat_[row][col] = t_array_2_d[row][col];
      }
    }
  }

  Mat4::Mat4(const Vec4<float>& t_row0, const Vec4<float>& t_row1
    , const Vec4<float>& t_row2, const Vec4<float>& t_row3)
  {
    m_mat_[0][X] = t_row0.x;
    m_mat_[0][Y] = t_row0.y;
    m_mat_[0][Z] = t_row0.z;
    m_mat_[0][T] = t_row0.t;

    m_mat_[1][X] = t_row1.x;
    m_mat_[1][Y] = t_row1.y;
    m_mat_[1][Z] = t_row1.z;
    m_mat_[1][T] = t_row1.t;

    m_mat_[2][X] = t_row2.x;
    m_mat_[2][Y] = t_row2.y;
    m_mat_[2][Z] = t_row2.z;
    m_mat_[2][T] = t_row2.t;

    m_mat_[3][X] = t_row3.x;
    m_mat_[3][Y] = t_row3.y;
    m_mat_[3][Z] = t_row3.z;
    m_mat_[3][T] = t_row3.t;
  }

  // ___ operators __________________________________________________________
  Mat4& Mat4::operator*=(const Mat4& t_other)
  {
    return *this = *this * t_other;
  }

  Mat4& Mat4::operator*=(const float t_scalar)
  {
    for (auto& row : m_mat_)
    {
      for (auto& col : row)
      {
        col *= t_scalar;
      }
    }
    return *this;
  }

  Mat4 Mat4::operator*(const Mat4& t_other) const
  {
    Mat4 temp;
    for (auto this_row = 0; this_row < SIZE; ++this_row)
    {
      for (auto other_col = 0; other_col < SIZE; ++other_col)
      {
        for (auto this_col_other_row = 0; this_col_other_row < SIZE; ++this_col_other_row)
        {
          temp.m_mat_[this_row][other_col] += m_mat_[this_row][this_col_other_row]
            * t_other.m_mat_[this_col_other_row][other_col];
        }
      }
    }
    return temp;
  }

  Mat4 Mat4::operator*(const float t_scalar) const
  {
    Mat4 temp;
    for (auto row = 0; row < SIZE; ++row)
    {
      for (auto col = 0; col < SIZE; ++col)
      {
        temp.m_mat_[row][col] = m_mat_[row][col] * t_scalar;
      }
    }
    return temp;
  }

  Vec3<float> Mat4::operator*(const Vec3<float>& t_other) const
  {
    Vec3<float> temp;
    for (auto this_row = 0; this_row < SIZE; ++this_row)
    {
      temp.x += m_mat_[this_row][X] * t_other.x;
      temp.y += m_mat_[this_row][Y] * t_other.y;
      temp.z += m_mat_[this_row][Z] * t_other.z;
    }
    return temp;
  }

  Vec4<float> Mat4::operator*(const Vec4<float>& t_other) const
  {
    Vec4<float> temp;
    for (auto this_row = 0; this_row < SIZE; ++this_row)
    {
      temp.x += m_mat_[this_row][X] * t_other.x;
      temp.y += m_mat_[this_row][Y] * t_other.y;
      temp.z += m_mat_[this_row][Z] * t_other.z;
      temp.t += m_mat_[this_row][T] * t_other.t;
    }
    return temp;
  }

  bool Mat4::operator==(const Mat4& t_other) const
  {
    for (auto row = 0; row < SIZE; ++row)
    {
      for (auto col = 0; col < SIZE; ++col)
      {
        if (m_mat_[row][col] != t_other.m_mat_[row][col])
        {
          return false;
        }
      }
    }
    return true;
  }

  std::string Mat4::to_string() const
  {
    std::string str;
    for (auto& row : m_mat_)
    {
      str += '\n';
      for (auto& col : row)
      {
        str += ' '+Demo_center::double_to_2_points_string(col);
      }
    }
    str += '\n';

    return str;
  }

  Vec3<float> Mat4::get_multiplied(const Vec3<float>& t_other) const
  {
    return *this*t_other;
  }

  Vec4<float> Mat4::get_multiplied(const Vec4<float>& t_other) const
  {
    return *this*t_other;
  }

  void Mat4::multiply(const Mat4& t_other)
  {
    *this *= t_other;
  }

  void Mat4::invert()
  {
    float det = 0;
    for (auto col = 0; col < SIZE; col++)
    {
      det += m_mat_[0][col] * ( 
        m_mat_[1][(col + 1) % SIZE] * m_mat_[2][(col + 2) % SIZE] 
        - m_mat_[1][(col + 2) % SIZE] * m_mat_[2][(col + 1) % SIZE] );
    }

    Mat4 temp;
    for (auto row = 0; row < SIZE; row++) 
    {
      for (auto col = 0; col < SIZE; col++)
      {
        temp.m_mat_[row][col] = (
          m_mat_[(col + 1) % SIZE][(row + 1) % SIZE] 
            * m_mat_[(col + 2) % SIZE][(row + 2) % SIZE]
          - m_mat_[(col + 1) % 3][(row + 2) % 3] 
            * m_mat_[(col + 2) % 3][(row + 1) % 3]
          ) / det;
      }
    }
    *this = temp;
  }
}//G6037599