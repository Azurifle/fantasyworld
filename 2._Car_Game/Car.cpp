#include "stdafx.h"
#include "Car.hpp"
#include "0._Game_Engine/Grid.hpp"
#include "0._Game_Engine/Game_engine.hpp"

namespace G6037599
{
  //___ constructors _____________________________________________
  Car::Car(const std::string& t_name, const std::string& t_shape
    , const float t_speed, const int t_id, const int t_max_fuel)
    : m_name_(t_name), m_shape_(t_shape)
      , m_pos_(Grid::NOT_SPAWN), m_face_(COORD{0, 0})
      , m_speed_(t_speed), m_wait_milisecs_(0.0f), m_id_(t_id)
      , m_max_fuel_(t_max_fuel), m_fuel_(t_max_fuel) {}

  //___ public _____________________________________________
  void Car::spawned(const std::shared_ptr<Grid>& t_track)
  {
    m_track_ = t_track;
    m_pos_ = m_track_->spawns(m_id_, m_shape_);
    //m_face_
  }

  /*___ Speed _________________________________
  | slowest speed: 0.1 = 1 tiles/10 secs       |
  | Fastest speed: 500.0 = 1 tiles/20 milisecs |
  |___________________________________________*/

  int Car::runs()
  {
    if (m_pos_.X == Grid::NOT_SPAWN.X)
    {
      return 0;
    }

    m_wait_milisecs_ += Game_engine::get_delta_milisec();
    const auto SECOND = 1000.0f;
    if(m_wait_milisecs_ >= SECOND/m_speed_)
    {
      m_wait_milisecs_ -= SECOND / m_speed_;
      
      enum Enum 
      {
        NORTH_WEST, NORTH, NORTH_EAST, EAST
        , SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, DIRECTIONS
      };

      COORD moved;
      auto i = 0;
      const auto LOOP_LIMIT = 10;
      do
      {
        moved = m_pos_;
        switch (rand() % DIRECTIONS)
        {
        case NORTH_WEST: --moved.X; --moved.Y; break;
        case NORTH: --moved.Y; break;
        case NORTH_EAST: ++moved.X; --moved.Y; break;
        case EAST: ++moved.X; break;
        case SOUTH_EAST: ++moved.X; ++moved.Y; break;
        case SOUTH: ++moved.Y; break;
        case SOUTH_WEST: --moved.X; ++moved.Y; break;
        default: --moved.X;
        }
        ++i;
        if(i > LOOP_LIMIT) { return m_fuel_; }
      } while (!m_track_->moved(m_pos_, m_id_, m_shape_, moved));

      --m_fuel_;
      switch (m_fuel_)
      {
      case 0: m_track_->despawns(m_pos_, m_id_); default:;
      }

      //change to follow 4 points if have time
    }
    return m_fuel_;
  }

  void Car::set_id(const int t_id)
  {
    REQUIRE(t_id > 0);

    if(m_pos_.X != Grid::NOT_SPAWN.X)
    {
      m_track_->set(m_pos_, m_id_, t_id);
    }//already spawned on track
    m_id_ = t_id;
  }
}//G6037599