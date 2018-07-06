#include "stdafx.h"
#include "Star.hpp"

namespace G6037599
{
  // ___ constructor ______________________________________________________
  Star::Star(const Vec3<float>& t_start_pos, const Vec3<float>& t_end_pos
    , const float t_rotate_speed, const float t_blink_rate) 
    : m_pos_(t_start_pos), m_end_pos_(t_end_pos), m_rotate_speed_(t_rotate_speed)
      , m_z_degrees_(0)
  {
    static const auto START_SCALE = 0.01f;//0.08f
    m_scale_ = Vec3<float>(START_SCALE);

    static const auto INNER_RADIUS = Vec3<float>(0, 0.7f, 0)
      , TIP_SCALE = Vec3<float>(0.5f, 1, 1);
    m_5_tips_.resize(5, Triangle(INNER_RADIUS, TIP_SCALE));

    float tip_degree = 0;
    for (unsigned i = 0; i < m_5_tips_.size(); ++i)
    {
      static const auto DEGREES_PER_SEC = 180.0f;
      m_5_tips_[i].rotate_speed = t_blink_rate * DEGREES_PER_SEC;

      m_5_tips_[i].z_degree = tip_degree;
      static const auto DEGREE_BETWEEN_TIP = 72;
      tip_degree += DEGREE_BETWEEN_TIP;
    }
  }

  // ___ public ______________________________________________________________
  void Star::update(const float t_delta_seconds)
  {
    m_z_degrees_ += m_rotate_speed_ * t_delta_seconds;

    glPushMatrix();
      glTranslatef(m_pos_.x, m_pos_.y, m_pos_.z);
      glRotatef(m_z_degrees_, 0, 0, 1);
      glScalef(m_scale_.x, m_scale_.y, m_scale_.z);
      
      for (unsigned i = 0; i < m_5_tips_.size(); ++i)
      {
        m_5_tips_[i].update(t_delta_seconds);
      }
    glPopMatrix();
  }
}//G6037599