#include "stdafx.h"
#include "Screen_saver.hpp"
#include "Triangle.hpp"
#include "Demo_Center/Demo_Center.hpp"

namespace G6037599
{
  // ___ static ___________________________________________________________
  void Screen_saver::run()
  {
    static auto is_running = false;
    REQUIRE(!is_running);
    is_running = true;

    const auto WINDOW = glfw_window();

    const auto SCALE = Vec3<float>(0.5f);
    Triangle tri1(Vec3<float>(-0.5f, 0, 0), SCALE);
    Triangle tri2(Vec3<float>(0.5f, 0, 0), SCALE);

    while (!glfwWindowShouldClose(WINDOW))
    {
      Demo_center::reset_delta_seconds();
      glClear(GL_COLOR_BUFFER_BIT);//render BG
      glClearColor(0, 0, 0, 1);//change BG color

      tri1.render();
      tri2.render();

      glfwSwapBuffers(WINDOW);
      glfwPollEvents();//clear inputs
    }
    glfwTerminate();
  }

  // ___ private static ______________________________________________________
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
    if (t_key == GLFW_KEY_E && t_action == GLFW_PRESS)
    {
      std::cout << "I pressed E" << std::endl;
    }
  }

}//G6037599