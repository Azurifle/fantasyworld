#include "stdafx.h"
#include "Triangle.hpp"

namespace G6037599
{
  // ___ constructor __________________________________________________________
  Triangle::Triangle(const Vec3<float>& t_pos, const Vec3<float>& t_rotation
    , const Vec3<float>& t_scale)
    : pos(t_pos), rotation(t_rotation), scale(t_scale), t(0), speed(0.1f) {}

  void Triangle::draw()
  {
    glPushMatrix();
      glTranslatef(pos.x, pos.y, pos.z);
      glRotatef(t, rotation.x, rotation.y, rotation.z);
      glScalef(scale.x, scale.y, scale.z);

      glBegin(GL_TRIANGLES);
        paint_pos(Vec3<float>(-1, 0, 0), Vec3<float>(1, 0, 0));
        paint_pos(Vec3<float>(0, 1, 0), Vec3<float>(1, 0, 1));
        paint_pos(Vec3<float>(1, 0, 0), Vec3<float>(0, 1, 0));
      glEnd();
    glPopMatrix();

    t += speed;
  }

  // ___ private static ______________________________________________________
  void Triangle::paint_pos(const Vec3<float>& t_pos, const Vec3<float>& t_rgb)
  {
    glColor3f(t_rgb.x, t_rgb.y, t_rgb.z);
    glVertex3f(t_pos.x, t_pos.y, t_pos.z);
  }

}//G6037599