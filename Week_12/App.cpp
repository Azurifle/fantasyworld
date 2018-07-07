#include "stdafx.h"
#include "App.hpp"

namespace G6037599
{
  // ___ (de)constructors ________________________________________________
  App::App(const int t_width, const int t_height, const std::string& t_title)
  {
    switch (glfwInit())
    {
    case GLFW_FALSE: glfwTerminate(); PROMISE(false); default:;
    }

    m_window_ = glfwCreateWindow(t_width, t_height, t_title.c_str(), nullptr, nullptr);

    if (!m_window_)
    {
      glfwTerminate(); PROMISE(false);
    }

    glfwMakeContextCurrent(m_window_);
    
    const auto RESULT = glewInit();
    switch (RESULT) 
    { 
      case GLEW_OK: break;
      default: std::cout << "GLEW error: " << glewGetErrorString(RESULT) << std::endl; 
        PROMISE(false);
    }

    show_glew_version();
    test_alpha_bend_n_depth();
  }

  App::~App()
  {
    glfwTerminate();
  }

  // ___ public ________________________________________________
  void App::run()
  {
    while (!glfwWindowShouldClose(m_window_))
    {
      render_background();



      glfwSwapBuffers(m_window_);
      glfwPollEvents();//clear inputs
    }
  }

  // ___ private static ________________________________________________
  void App::show_glew_version()
  {
    const auto gl_version = glGetString(GL_VERSION)
      , shader_version = glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::cout << "GL version: " << gl_version << std::endl
      << "GLSL version: " << shader_version << std::endl;
  }

  void App::test_alpha_bend_n_depth()
  {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  void App::render_background()
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0, 0, 0, 1);//change BG color
  }
}//G6037599