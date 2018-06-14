#ifndef G6037599_CAR_HPP
#define G6037599_CAR_HPP
#pragma once

namespace G6037599
{
  class Grid;

  class Car
  {
  public:
    Car(const std::string& t_name, const std::string& t_shape
      , int t_id, int t_max_fuel, int t_speed);
    ~Car() = default;
    Car(const Car& t_to_copy) = default;
    Car& operator=(const Car& t_to_copy) = default;
    Car& operator=(Car&& t_to_move) noexcept = default;

    void spawned(const std::shared_ptr<Grid>& t_grid);
  private:
    std::string m_name_{}, m_shape_{};
    COORD m_pos_{};
    int m_id_, m_max_fuel_, m_fuel_, m_speed_;

    Car(Car&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_GAME_ENGINE_HPP