#ifndef G6037599_CAR_HPP
#define G6037599_CAR_HPP
#pragma once

namespace G6037599
{
  class Grid;

  class Car final
  {
  public:
    Car(const std::string& t_name, const std::string& t_shape
      , const std::shared_ptr<Grid>& t_track
      , float t_speed, int t_id, int t_max_fuel);
    ~Car() = default;
    Car(const Car& t_to_copy) = default;
    Car& operator=(const Car& t_to_copy) = default;
    Car& operator=(Car&& t_to_move) noexcept = default;

    void spawned();
    int runs();
    void set_id(int t_id);
  private:
    std::string m_name_{}, m_shape_{};
    COORD m_pos_{}, m_face_{};
    std::shared_ptr<Grid> m_track_{};
    float m_speed_, m_wait_milisecs_;
    int m_id_, m_max_fuel_, m_fuel_;

    Car(Car&& t_to_move) noexcept = default;
  };
}//G6037599

#endif //G6037599_GAME_ENGINE_HPP