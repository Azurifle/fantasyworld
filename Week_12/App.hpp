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
    static void step2_load_shader_codes(const std::vector<GLuint>& t_shader_program_ids);
    static void step4_check_compilation(GLuint t_shader_program_id);
    static void step7_check_linking(GLuint t_m_program_id);
    static void set_vertex_pointer(const std::vector<GLint>& t_vram_location);
    static void show_shader_error(GLuint t_shader_id, std::string t_text, bool t_is_program = true);
    static void enable_value_processing(const std::vector<GLint>& t_vram_location);

    void init_glfw_system(const std::string& t_title);
    void key_callback(GLFWwindow* t_window, int t_key, int t_scancode, int t_action, int t_mods);
    void init_shader_program();
    void init_mesh();
    void init_texture();
    void step1_create_shader_program(std::vector<GLuint>& t_shader_ids);
    void create_vertices_in_cpu_ram();
    void move_vertices_to_vram();
    void get_variables(std::vector<GLint>& t_vram_location);
    void render_objects() const;
    void model_view_projection(Mat4& t_out_mvp) const;
  };
}//G6037599

#endif //G6037599_APP_HPP
