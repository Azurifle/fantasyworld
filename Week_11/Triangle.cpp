#include "stdafx.h"
#include "Triangle.hpp"

namespace G6037599
{
  // ___ constructor __________________________________________________________
  Triangle::Triangle(const Vec3<float>& t_pos, const Vec3<float>& t_scale
    , const float t_degrees_per_sec) : pos(t_pos), scale(t_scale)
    , degrees_per_sec(t_degrees_per_sec), m_x_degrees_(0) {}

  void Triangle::update(const float t_delta_seconds)
  {
    m_x_degrees_ += degrees_per_sec * t_delta_seconds;

    glPushMatrix();
      glTranslatef(pos.x, pos.y, pos.z);
      glRotatef(m_x_degrees_, 1, 0, 0);
      glScalef(scale.x, scale.y, scale.z);

      glBegin(GL_TRIANGLES);
        const auto WHITE = Vec3<float>(1, 1, 1);
        paint_pos(Vec3<float>(-1, 0, 0), WHITE);
        glVertex3f(0, 1, 0);
        glVertex3f(1, 0, 0);
      glEnd();
    glPopMatrix();
  }

  // ___ private static ______________________________________________________
  void Triangle::paint_pos(const Vec3<float>& t_pos, const Vec3<float>& t_rgb)
  {
    glColor3f(t_rgb.x, t_rgb.y, t_rgb.z);
    glVertex3f(t_pos.x, t_pos.y, t_pos.z);
  }

}//G6037599