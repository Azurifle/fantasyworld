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

  Mat4 Mat4::translation(const Vec3<float>& t_translate)
  {
    Mat4 temp(1);
    temp.m_mat_[0][T] = t_translate.x;
    temp.m_mat_[1][T] = t_translate.y;
    temp.m_mat_[2][T] = t_translate.z;
    return temp;
  }

  Mat4 Mat4::rotation(const float t_radian_angle, const Vec3<int>& t_axis)
  {
    Mat4 rotation(1);

    switch(t_axis.x)
    {
    case 0: break; default: rotate(rotation, t_radian_angle, X);
    }
    switch (t_axis.y)
    {
    case 0: break; default: rotate(rotation, t_radian_angle, Y);
    }
    switch (t_axis.z)
    {
    case 0: break; default: rotate(rotation, t_radian_angle, Z);
    }

    return rotation;
  }

  Mat4 Mat4::scaling(const Vec3<float>& t_scale)
  {
    Mat4 temp(1);
    temp.m_mat_[0][X] = t_scale.x;
    temp.m_mat_[1][Y] = t_scale.y;
    temp.m_mat_[2][Z] = t_scale.z;
    return temp;
  }

  Mat4 Mat4::transpose(const Mat4& t_matrix)
  {
    Mat4 temp;
    for (auto row = 0; row < SIZE; ++row)
      for (auto col = 0; col < SIZE; ++col)
      {
        temp.m_mat_[row][col] = t_matrix.m_mat_[col][row];
      }
    return temp;
  }

  Mat4 Mat4::inverse(const Mat4& t_matrix)
  {
    //adapt from https://www.quora.com/How-do-I-make-a-C++-program-to-get-the-inverse-of-a-matrix-100-X-100

    Mat4 left(t_matrix), right(1);

    for (auto i = 0; i < SIZE; ++i)
    {
      make_left_reduced_row(t_matrix, left, right, i);
        
      for (auto row = 0; row < SIZE; ++row)
      {
        if (row == i) continue;

        make_left_reduced_echelon(left, right, i, row, left.m_mat_[row][i]);
      }
    }
    return right;
  }

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
  bool Mat4::operator==(const Mat4& t_other) const
  {
    for (auto row = 0; row < SIZE; ++row)
    {
      for (auto col = 0; col < SIZE; ++col)
      {
        if (abs(m_mat_[row][col] - t_other.m_mat_[row][col]) 
          > Demo_center::PRECISION)
        {
          return false;
        }
      }//col loop
    }
    return true;
  }

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

  // ___ friend _________________________________________________________________
  Vec4<float> operator*(const Mat4& t_left, const Vec4<float>& t_right)
  {
    Vec4<float> temp;
    for (auto row = 0; row < Mat4::SIZE; ++row)
    {
      temp.x += t_left.m_mat_[row][Mat4::X] * t_right.x;
      temp.y += t_left.m_mat_[row][Mat4::Y] * t_right.y;
      temp.z += t_left.m_mat_[row][Mat4::Z] * t_right.z;
      temp.t += t_left.m_mat_[row][Mat4::T] * t_right.t;
    }
    return temp;
  }

  // ___ public _________________________________________________________________
  std::string Mat4::to_string(const bool t_shows_float) const
  {
    std::string str;
    for (auto& row : m_mat_)
    {
      str += '\n';
      for (auto& col : row)
      {
        const auto points = 2;
        str += ' '+Demo_center::double_points_string(col, t_shows_float? points: 0);
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
    *this = inverse(*this);
  }

  void Mat4::set(const Vec2<int>& t_pos, const float t_value)
  {
    m_mat_[t_pos.x][t_pos.y] = t_value;
  }

  void Mat4::rotate(Mat4& t_in_out, const float t_radian_angle, const int t_axis)
  {
    const auto cos_angle = cos(t_radian_angle)
      , sin_angle = sin(t_radian_angle);

    Mat4 rot(1);
    rot.m_mat_[1][Y] = t_axis != Y ? cos_angle : 1;
    rot.m_mat_[2][Y] = t_axis == X ? sin_angle : 0;
    rot.m_mat_[1][Z] = -rot.m_mat_[2][Y];
    rot.m_mat_[2][Z] = t_axis != Z ? cos_angle : 1;

    rot.m_mat_[0][X] = t_axis != X ? cos_angle : 1;
    rot.m_mat_[0][Z] = t_axis == Y ? sin_angle : 0;
    rot.m_mat_[2][X] = -rot.m_mat_[0][Z];

    rot.m_mat_[1][X] = t_axis == Z ? sin_angle : 0;
    rot.m_mat_[0][Y] = -rot.m_mat_[1][X];
    t_in_out *= rot;
  }

  void Mat4::make_left_reduced_row(const Mat4& t_left, Mat4& t_out_left, Mat4& t_out_right, const int t_row)
  {
    make_up_triangle_1(t_out_left, t_row);
    t_out_right.m_mat_[t_row][t_row] /= t_left.m_mat_[t_row][t_row];
  }

  void Mat4::make_up_triangle_1(Mat4& t_in_out, const int t_row)
  {
    for (auto col = t_row; col < SIZE; ++col)
    {
      t_in_out.m_mat_[t_row][col] = 1;
    }
  }

  void Mat4::make_left_reduced_echelon(Mat4& t_left, Mat4& t_right, const int t_i
    , const int t_row, const float t_left_diagonal)
  {
    for (auto col = 0; col < SIZE; ++col)
    {
      t_left.m_mat_[t_row][col] -= t_left_diagonal * t_left.m_mat_[t_i][col];
      t_right.m_mat_[t_row][col] -= t_left_diagonal * t_right.m_mat_[t_i][col];
    }
  }

}//G6037599