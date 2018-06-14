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
      const auto A_QUARTER_SECOND = 250;
      Sleep(A_QUARTER_SECOND);
      switch (Game_engine::get_key())
      {
      case Game_engine::KEY_NO_PRESS: break;
      case Game_engine::KEY_ESC: return;
      default:;
      }
    }//game loop
  }

  //___ private static _____________________________________________
  bool Car_game::m_is_running_ = false;

  //___ private constructor _____________________________________________
  Car_game::Car_game()
  {
    const COORD TRACK_START = { 1, 3 }, TRACK_END = { 85, 35 };
    m_track_ = std::make_shared<Grid>(TRACK_START, TRACK_END);
    
    const std::string GAME_FOLDER("2._Car_Game/");
    const auto JSON_CONFIG = nlohmann::json::parse(std::ifstream(GAME_FOLDER + "0. Config.json"));

    std::vector<std::string> track_names = JSON_CONFIG["track_names"];
    m_track_->load(GAME_FOLDER + track_names[0] +".bmp");
    m_track_->print();

    std::vector<std::string> car_names = JSON_CONFIG["car_names"];
    for(unsigned i = 0; i < car_names.size(); ++i)
    {
      const auto JSON_CAR = nlohmann::json::parse(
        std::ifstream(GAME_FOLDER + car_names[i] +".json"));

      m_cars_.push_back(std::make_unique<Car>(
          car_names[i]
          , JSON_CAR["shape"].get<std::string>()
          , JSON_CAR["max_fuel"].get<int>(), JSON_CAR["speed"].get<int>()
        ));
    }
  }
}//G6037599