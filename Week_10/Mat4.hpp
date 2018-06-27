#ifndef G6037599_MAT4_HPP
#define G6037599_MAT4_HPP
#pragma once

namespace G6037599
{
  class Mat4 final
  {
  public:
    enum Enum { SIZE  = 4 };

    explicit Mat4(float t_all_value = 0.0f);
    ~Mat4() = default;
    Mat4(const Mat4& t_to_copy) = default;
    Mat4(Mat4&& t_to_move) noexcept = default;
    Mat4& operator = (const Mat4& t_to_copy) = default;
    Mat4& operator = (Mat4&& t_to_move) noexcept = default;

    std::string to_string() const;
  private:
    float m_matrix_[SIZE][SIZE]{};

    static void assign_all_cols(float(&t_row)[SIZE], float t_all_value);
  };
}//G6037599

#endif //G6037599_MAT4_HPP
