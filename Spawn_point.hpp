#ifndef SPAWN_POINT
#define SPAWN_POINT
#pragma once

namespace G6037599
{
  class Unit;
  class Type_data;
  class Tile_data;
  class Map;
  class Console;

  class Spawn_point
  {
  public:
    Spawn_point(std::shared_ptr<Type_data> t_type
      , std::shared_ptr<Console> t_m_console, std::shared_ptr<Map> t_m_map);
    ~Spawn_point() = default;
    Spawn_point(const Spawn_point& t_to_copy);
    Spawn_point& operator=(const Spawn_point& t_to_copy);

    COORD get_pos() const;
  private:
    std::vector<std::unique_ptr<Unit>> m_monsters_;
    std::shared_ptr<Type_data> m_type_ = nullptr;
    std::shared_ptr<Console> m_console_ = nullptr;
    std::shared_ptr<Map> m_map_ = nullptr;
    std::unique_ptr<Tile_data> m_tile_ = nullptr;
    const char* m_symbol_ = "XM";
    int m_monster_count_ = 0;

    void copy_from(const Spawn_point& t_to_copy);
  };
}//G6037599

#endif //SPAWN_POINT