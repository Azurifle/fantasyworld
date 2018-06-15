#include "stdafx.h"
#include "Car_game.hpp"
#include "0._Game_Engine/Game_engine.hpp"
#include "0._Game_Engine/Grid.hpp"
#include "0._Game_Engine/json.hpp"

namespace G6037599
{
  //___ static _____________________________________________
  void Car_game::run()
  {
    REQUIRE(Game_engine::is_running());
    REQUIRE(!m_is_running_);
    Car_game game;

    while (true)
    {
      Sleep(Game_engine::FPS_50);
      switch (Game_engine::get_key())
      {
      case Game_engine::KEY_ESC: return;
      default: game.update();
      }
    }//game loop
  }

  //___ private static _____________________________________________
  bool Car_game::m_is_running_ = false;

  //___ private constructor _____________________________________________
  Car_game::Car_game() : m_1_st_spawned_(Grid::NO_GAME_OBJECT+1)
  {
    const COORD TRACK_START = { 1, 3 }, TRACK_END = { 85, 35 };
    m_track_ = std::make_shared<Grid>(TRACK_START, TRACK_END);
    
    const std::string GAME_FOLDER("2._Car_Game/");
    const auto JSON_CONFIG = nlohmann::json::parse(std::ifstream(
      GAME_FOLDER + "0. Config.json"));
    
    std::vector<std::string> track_names = JSON_CONFIG["track_names"];
    m_track_->load(GAME_FOLDER + track_names[0] +".bmp");
    m_track_->print();

    std::vector<std::string> car_types = JSON_CONFIG["car_names"];
    for(unsigned i = 0; i < car_types.size(); ++i)
    {
      const auto JSON_CAR = nlohmann::json::parse(
        std::ifstream(GAME_FOLDER + car_types[i] +".json"));

      m_cars_.push_back(std::make_unique<Car>(
        car_types[i], JSON_CAR["shape"].get<std::string>()
        , JSON_CAR["speed"].get<float>()
        , i, JSON_CAR["max_fuel"].get<int>()
        ));
    }

    m_1_st_spawned_ = m_cars_.size();
    m_cars_.push_back(std::make_unique<Car>(*m_cars_[rand() % car_types.size()]));
    m_cars_[m_1_st_spawned_]->set_id(m_1_st_spawned_);
    m_cars_[m_1_st_spawned_]->spawned(m_track_);
  }

  //___ private _____________________________________________
  void Car_game::update()
  {
    for(auto i = m_1_st_spawned_; i < m_cars_.size(); ++i)
    {
      switch (m_cars_[i]->runs(m_track_))
      {
      case 0: m_cars_.erase(m_cars_.begin() + i); 
        for (auto replace = i; replace < m_cars_.size(); ++replace)
        {
          m_cars_[replace]->set_id(replace);
        }
        default:;
      }//fuel empty
    }//each cars runs
  }
}//G6037599