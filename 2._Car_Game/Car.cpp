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
      , m_speed_(t_speed), m_wait_to_run_(0.0f)
      , m_id_(t_id), m_max_fuel_(t_max_fuel), m_fuel_(t_max_fuel) {}

  //___ public _____________________________________________
  void Car::spawned(const std::shared_ptr<Grid>& t_track)
  {
    m_track_ = t_track;
    m_pos_ = m_track_->spawns(m_id_, m_shape_);

    const auto EAST = COORD{ 1, 0 }, WEST = COORD{ -1, 0 };
    m_face_ = m_pos_.Y < m_track_->find_middle_pos().Y ? EAST : WEST;
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

    m_wait_to_run_ += m_speed_ * Game_engine::get_delta_time();

    const auto RUN = 1.0f;
    if(m_wait_to_run_ >= RUN)
    {
      --m_wait_to_run_;

      switch (--m_fuel_)
      {
      case 0: m_track_->despawns(m_pos_, m_id_); 
        return m_fuel_; default:;
      }

      const auto FORWARD = COORD{ m_pos_.X + m_face_.X, m_pos_.Y + m_face_.Y };
      switch (m_track_->moved(m_pos_, m_id_, m_shape_, FORWARD))
      {
      case true: break;
      default: //random front until 10 then back
        const auto STOP_RANDOM_FACE = 8;
        for (auto i = 1; i <= STOP_RANDOM_FACE; ++i)
        {
          enum Direction
          {
            EAST = 1, SOUTH = 1, WEST = -1, NORTH = -1
          };
          std::vector<COORD> directions(8);
          directions.push_back(COORD{ EAST, 0 });
          directions.push_back(COORD{ EAST, SOUTH });
          directions.push_back(COORD{ 0, SOUTH });
          directions.push_back(COORD{ WEST, SOUTH });
          directions.push_back(COORD{ WEST, 0 });
          directions.push_back(COORD{ WEST, NORTH });
          directions.push_back(COORD{ 0, NORTH });

          //switch face
          //random 4 faces 8 times ! change face
          //random 3 backs 4 times change face to slight right
        }
      }
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