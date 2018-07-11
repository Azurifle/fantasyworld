#include <stdafx.h>
#include "App.hpp"
#include "Vertex.hpp"
#include "My_Math/Mat4.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "Thirdparty/stb_image.h"//no include guard

namespace G6037599
{
  //adapt from https://github.com/redeian/FirstGLFW

  // ___ (de)constructors ________________________________________________
  App::App(const int t_width, const int t_height, const std::string& t_title) 
    : m_width_(t_width), m_height_(t_height), m_is_active_(true)
  {
    init_glfw_system(t_title);
    
    const auto RESULT = glewInit();
    switch (RESULT) 
    { 
      case GLEW_OK: break;
      default: std::cout << "GLEW error: " << glewGetErrorString(RESULT) << std::endl; 
        PROMISE(false);
    }

    show_glew_versions();
    test_depth_n_alpha_bend();

    init_shader_program();
    init_mesh();
    init_texture();
  }

  App::~App()
  {
    glfwTerminate();
    puts("App destroyed.");
  }

  // ___ public ________________________________________________
  void App::run() const
  {
    while (!glfwWindowShouldClose(m_window_))
    {
      render_background();
      switch (m_is_active_) { case true: render_objects(); default:; }
      glfwSwapBuffers(m_window_);
      glfwPollEvents();//clear inputs
    }
  }

  // ___ private static ________________________________________________
  void App::key_callback_static(GLFWwindow* t_window, const int t_key
    , const int t_scancode, const int t_action, const int t_mods)
  {
    auto that = static_cast<App*>(glfwGetWindowUserPointer(t_window));
    that->key_callback(t_window, t_key, t_scancode, t_action, t_mods);
  }

  void App::show_glew_versions()
  {
    std::cout 
      << "Graphic Driver OpenGL version: " << glGetString(GL_VERSION) << std::endl 
      << "Shading language version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) 
      << std::endl;
  }

  void App::test_depth_n_alpha_bend()
  {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  }

  void App::render_background()
  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const Vec3<float> BG_BLUE_GREEN(0, 0.3f, 0.8f);
    glClearColor(BG_BLUE_GREEN.x, BG_BLUE_GREEN.y, BG_BLUE_GREEN.z, 1);
  }

  void App::add_to_shader_source(const char* const& t_vertex_shader_code
    , const char* const& t_fragment_shader_code
    , GLuint& t_vertex_shader_id, GLuint& t_fragment_shader_id)
  {
    glShaderSource(t_vertex_shader_id, 1, &t_vertex_shader_code, nullptr);
    glShaderSource(t_fragment_shader_id, 1, &t_fragment_shader_code, nullptr);
  }

  void App::step3_compile_codes(const GLuint t_vertex_shader_id
    , const GLuint t_fragment_shader_id)
  {
    glCompileShader(t_vertex_shader_id);
    glCompileShader(t_fragment_shader_id);
    //3.1 Check the compiling code https://d.pr/D63ZbS
  }

  void App::set_vertex_pointer(std::vector<GLint> t_vram_location)
  {
    enum Enum
    {
      POS, COLOR, TEXTURE, TEXTURE_XY = 2, XYZ_RGB
      , XYZ_RGB_SIZE = sizeof(float) * XYZ_RGB
    };
    glVertexAttribPointer(t_vram_location[POS], XYZ_RGB, GL_FLOAT, GL_FALSE
      , sizeof(Vertex), nullptr);
    glVertexAttribPointer(t_vram_location[COLOR], XYZ_RGB, GL_FLOAT, GL_FALSE
      , sizeof(Vertex), reinterpret_cast<void*>(XYZ_RGB_SIZE));
    glVertexAttribPointer(t_vram_location[TEXTURE], TEXTURE_XY, GL_FLOAT, GL_FALSE
      , sizeof(Vertex), reinterpret_cast<void*>(XYZ_RGB_SIZE * TEXTURE_XY));
  }

  // ___ private ___________________________________________________________
  void App::init_glfw_system(const std::string& t_title)
  {
    switch (glfwInit())
    {
    case GLFW_FALSE: glfwTerminate(); PROMISE(false); default:;
    }

    m_window_ = glfwCreateWindow(m_width_, m_height_, t_title.c_str(), nullptr, nullptr);
    if (!m_window_)
    {
      glfwTerminate(); PROMISE(false);
    }

    glfwMakeContextCurrent(m_window_);
    glfwSetWindowUserPointer(m_window_, this);
    glfwSetKeyCallback(m_window_, key_callback_static);
  }

  void App::key_callback(GLFWwindow* t_window, const int t_key
    , const int t_scancode, const int t_action, const int t_mods)
  {
    if (t_key == GLFW_KEY_E && t_action == GLFW_PRESS)
    {
      m_is_active_ = !m_is_active_;
      std::cout << (m_is_active_? "Activate window: " :"Deactivate window: ") << t_window
        << ", scancode: " << t_scancode << ", mods: " << t_mods << std::endl;
    }
  }

  void App::init_shader_program() 
  {
    //1. write 2 shader programs
    static auto VERTEX_SHADER_CODE =
      "uniform mat4 MVP; \n"	//MVP is Model View Projection
      "attribute vec3 vPos; \n"
      "attribute vec3 vCol; \n"
      "attribute vec2 vTex; \n"
      "varying vec3 color; \n"
      "varying vec2 texCoord; \n"
      "void main() \n "
      "{ \n"
      "   gl_Position = MVP * vec4(vPos, 1.0); \n"
      "   color = vCol; \n"
      "   texCoord = vTex; \n"
      "} \n"

      , FRAGMENT_SHADER_CODE = //color & texture
      "uniform sampler2D texture; \n"
      "varying vec3 color; \n"
      "varying vec2 texCoord; \n"
      "void main() \n"
      "{ \n"
      "    gl_FragColor = texture2D( texture, texCoord);\n"
      "} \n";

    GLuint vertex_shader_id, fragment_shader_id;
    step2_load_shader(VERTEX_SHADER_CODE, FRAGMENT_SHADER_CODE
      , vertex_shader_id, fragment_shader_id);

    step3_compile_codes(vertex_shader_id, fragment_shader_id);
    step4_attach_codes_to_program(vertex_shader_id, fragment_shader_id);
    glLinkProgram(m_program_id_);//5. link codes to program
  }

  void App::init_mesh()
  {
    create_vertices_in_cpu_ram();
    move_vertices_to_vram();

    std::vector<GLint> vram_location;
    get_variables(vram_location);
    enable_value_processing(vram_location);
    set_vertex_pointer(vram_location);
  }

  void App::init_texture()
  {
    glGenTextures(1, &m_texture_id_);
    glBindTexture(GL_TEXTURE_2D, m_texture_id_);

    int img_width, img_height, components;
    const auto TEXTURE_IMG = stbi_load("texture.png", &img_width, &img_height, &components, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB8_ALPHA8, img_width, img_height,
      0, GL_RGBA, GL_UNSIGNED_BYTE, TEXTURE_IMG);

    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  }

  void App::step2_load_shader(const char* const& t_vertex_shader_code
    , const char* const& t_fragment_shader_code
    , GLuint& t_vertex_shader_id, GLuint& t_fragment_shader_id)
  {
    m_program_id_ = glCreateProgram();
    t_vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    t_fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);

    add_to_shader_source(t_vertex_shader_code, t_fragment_shader_code
                         , t_vertex_shader_id, t_fragment_shader_id);
  }

  void App::step4_attach_codes_to_program(const GLuint t_vertex_shader_id
    , const GLuint t_fragment_shader_id) const
  {
    glAttachShader(m_program_id_, t_vertex_shader_id);
    glAttachShader(m_program_id_, t_fragment_shader_id);
  }

  void App::create_vertices_in_cpu_ram()
  {
    const auto GREEN = Vec3<float>(0, 1, 0), BLUE = Vec3<float>(0, 0, 1)
               , RED = Vec3<float>(1, 0, 0);
    m_vertices_.push_back(Vertex(Vec3<float>(-0.6f, -0.4f, 0), GREEN, Vec2<float>(0, 0)));
    m_vertices_.push_back(Vertex(Vec3<float>(0.6f, -0.4f, 0), BLUE, Vec2<float>(0, 1)));
    m_vertices_.push_back(Vertex(Vec3<float>(0, 0.6f, 0), RED, Vec2<float>(1, 1)));
  }

  void App::move_vertices_to_vram()
  {
    glGenVertexArrays(1, &m_vertex_array_id_);
    glBindVertexArray(m_vertex_array_id_);

    GLuint buffer_id;
    glGenBuffers(1, &buffer_id);
    glBindBuffer(GL_ARRAY_BUFFER, buffer_id);
    glBufferData(GL_ARRAY_BUFFER, m_vertices_.size() * sizeof(Vertex)
      , m_vertices_.data(), GL_STATIC_DRAW);
  }

  void App::get_variables(std::vector<GLint>& t_vram_location)
  {
    m_mvp_location_ = glGetUniformLocation(m_program_id_, "MVP");
    t_vram_location.push_back(glGetAttribLocation(m_program_id_, "vPos"));
    t_vram_location.push_back(glGetAttribLocation(m_program_id_, "vCol"));
    t_vram_location.push_back(glGetAttribLocation(m_program_id_, "vTex"));
  }

  void App::enable_value_processing(std::vector<GLint> t_vram_location)
  {
    for (auto i : t_vram_location)
    {
      glEnableVertexAttribArray(i);
    }
  }

  void App::render_objects() const
  {
    glViewport(0, 0, m_width_, m_height_);

    Mat4 MVP;
    model_view_projection(MVP);

    glUseProgram(m_program_id_);
    glBindTexture(GL_TEXTURE_2D, m_texture_id_);
    glUniformMatrix4fv(m_mvp_location_, 1, GL_FALSE, MVP.to_array());

    glBindVertexArray(m_vertex_array_id_);

    glDrawArrays(GL_TRIANGLES, 0, 3);
  }

  void App::model_view_projection(Mat4& t_out_mvp) const
  {
    const auto ANGLE = static_cast<float>(round(glfwGetTime()))
      , RATIO = m_width_ / static_cast<float>(m_height_);
    const auto ROTATE_MAT = Mat4::rotation(ANGLE, Vec3<int>(0, 0, 1))
      , MODEL_MAT = Mat4::translation(Vec3<float>(0)) * ROTATE_MAT * Mat4::scaling(Vec3<float>(1))
      , VIEW_PROJECTION = Mat4::ortho(-RATIO, RATIO, -1, 1, 1, -1);
    t_out_mvp = MODEL_MAT * VIEW_PROJECTION;
  }

}//G6037599