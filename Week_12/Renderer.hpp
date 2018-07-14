#ifndef G6037599_RENDERER_HPP
#define G6037599_RENDERER_HPP
#pragma once

namespace G6037599
{
  class Renderer final
  {
  public:
    static void use_shader(GLuint t_shader);
  private:
    Renderer() = default;
    ~Renderer() = default;
    Renderer(const Renderer& t_to_copy) = default;
    Renderer(Renderer&& t_to_move) noexcept = default;
    Renderer& operator = (const Renderer& t_to_copy) = default;
    Renderer& operator = (Renderer&& t_to_move) noexcept = default;
  };
}//G6037599

#endif G6037599_RENDERER_HPP;