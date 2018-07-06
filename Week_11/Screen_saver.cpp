#include "stdafx.h"
#include "Screen_saver.hpp"
#include "Triangle.hpp"

namespace G6037599
{
  // ___ static ___________________________________________________________
  void Screen_saver::run()
  {
    static auto is_running = false;
    REQUIRE(!is_running);
    is_running = true;

    const auto WINDOW = glfw_window();
    while (!glfwWindowShouldClose(WINDOW))
    {
      render_background();
      m_instance_.update();
      glfwSwapBuffers(WINDOW);
      glfwPollEvents();//clear inputs
    }
    glfwTerminate();
  }

  // ___ private static ______________________________________________________
  Screen_saver Screen_saver::m_instance_{};

  GLFWwindow* Screen_saver::glfw_window()
  {
    switch (glfwInit())
    {
    case GLFW_FALSE: glfwTerminate(); PROMISE(false); default:;
    }

    const auto WINDOW_WIDTH = 640, WINDOW_HEIGHT = 480;
    const auto WINDOW = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Screen Saver: Air Galley"
      , nullptr, nullptr);

    if (!WINDOW)
    {
      glfwTerminate(); PROMISE(false);
    }

    glfwMakeContextCurrent(WINDOW);
    glfwSetKeyCallback(WINDOW, key_callback);

    return WINDOW;
  }

  void Screen_saver::key_callback(GLFWwindow* t_window, const int t_key
    , const int t_scan_code, const int t_action, const int t_mods)
  {
    if (t_key == GLFW_KEY_E && t_action == GLFW_REPEAT)
    {
      std::cout << "I pressed E" << std::endl;
    }
  }

  void Screen_saver::render_background()
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);//change BG color
  }

  // ___ private constructor ___________________________________________________
  Screen_saver::Screen_saver()
  {
    m_triangles_.resize(2);
    m_triangles_[0].pos.x = -0.5f;
    m_triangles_[1].pos.x = 0.5f;
    m_triangles_[1].scale = m_triangles_[0].scale = Vec3<float>(0.5f);
  }

  // ___ private ________________________________________________________________
  void Screen_saver::update()
  {
    m_delta_time_.reset();
    m_triangles_[0].update(m_delta_time_.float_seconds());
    m_triangles_[1].update(m_delta_time_.float_seconds());
  }
}//G6037599