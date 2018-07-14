#ifndef G6037599_MESH_HPP
#define G6037599_MESH_HPP
#pragma once

namespace G6037599
{
  class Mesh final
  {
  public:
    //static GLuint create(const std::string& t_vertex_shader_code, const std::string& t_fragment_shader_code);
  private:
    Mesh() = default;
    ~Mesh() = default;
    Mesh(const Mesh& t_to_copy) = default;
    Mesh(Mesh&& t_to_move) noexcept = default;
    Mesh& operator = (const Mesh& t_to_copy) = default;
    Mesh& operator = (Mesh&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_MESH_HPP
