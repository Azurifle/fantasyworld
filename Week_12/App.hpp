#ifndef G6037599_APP_HPP
#define G6037599_APP_HPP
#pragma once
#include "My_Math/Mat4.hpp"

namespace G6037599
{
  struct Vertex;

  class App final
  {
  public:
    App(int t_width, int t_height, const std::string& t_title);
    ~App();
    App(const App& t_to_copy) = default;
    App(App&& t_to_move) noexcept = default;
    App& operator = (const App& t_to_copy) = default;
    App& operator = (App&& t_to_move) noexcept = default;

    void run() const;
  private:
    std::vector<Vertex> m_vertices_{};
    GLFWwindow* m_window_{};
    GLuint m_program_id_{}, m_vertex_array_id_{}, m_texture_id_{};
    GLint m_mvp_location_{};
    int m_width_, m_height_;
    bool m_is_active_;

    static void key_callback_static(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods);
    static void show_glew_versions();
    static void test_depth_n_alpha_bend();
    static void render_background();
    static void add_to_shader_source(const char*const& t_vertex_shader_code
      , const char*const& t_fragment_shader_code
      , GLuint& t_vertex_shader_id, GLuint& t_fragment_shader_id);
    static void step3_compile_codes(GLuint t_vertex_shader_id, GLuint t_fragment_shader_id);
    static void set_vertex_pointer(std::vector<GLint> t_vram_location);
    static void enable_value_processing(std::vector<GLint> t_vram_location);

    void init_glfw_system(const std::string& t_title);
    void key_callback(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods);
    void init_shader_program();
    void init_mesh();
    void init_texture();
    void step2_load_shader(const char*const& t_vertex_shader_code
      , const char*const& t_fragment_shader_code
      , GLuint& t_vertex_shader_id, GLuint& t_fragment_shader_id);
    void step4_attach_codes_to_program(GLuint t_vertex_shader_id, GLuint t_fragment_shader_id) const;
    void create_vertices_in_cpu_ram();
    void move_vertices_to_vram();
    void get_variables(std::vector<GLint>& t_vram_location);
    void render_objects() const;
    void model_view_projection(Mat4& t_out_mvp) const;
  };
}//G6037599

#endif //G6037599_APP_HPP
