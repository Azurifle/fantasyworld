#ifndef G6037599_APP_HPP
#define G6037599_APP_HPP
#pragma once

namespace G6037599
{
  class App final
  {
  public:
    App(int t_width, int t_height, const std::string& t_title);
    ~App();
    App(const App& t_to_copy) = default;
    App(App&& t_to_move) noexcept = default;
    App& operator = (const App& t_to_copy) = default;
    App& operator = (App&& t_to_move) noexcept = default;

    void run();
  private:
    GLFWwindow* m_window_{};

    static void show_glew_version();
    static void test_alpha_bend_n_depth();
    static void render_background();
  };
}//G6037599

#endif //G6037599_APP_HPP
