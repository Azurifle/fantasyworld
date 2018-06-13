#include "stdafx.h"
#include "Car_game.hpp"
#include "0._Game_Engine/Game_engine.hpp"
#include "0._Game_Engine/Grid.hpp"

namespace G6037599
{
  //___ static _____________________________________________
  void Car_game::run()
  {
    REQUIRE(Game_engine::is_running());
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

    /*
    for (auto row : map)
    {
      for (auto i : row)
      {
        std::cout << ' ';
        switch (i)
        {
        case 0: std::cout << ' '; break;
        default: std::cout << '-'; break;
        }
      }
      std::cout << std::endl;
    }
    _getch();*/
  }

  //___ private constructor _____________________________________________
  Car_game::Car_game()
  {
    const COORD TRACK_START = { 1, 2 }, TRACK_END = { 75, 30 };
    m_track_ = std::make_shared<Grid>(TRACK_START, TRACK_END);

    const std::string GAME_FOLDER("2._Car_Game/"), TRACKS_FOLDER("Tracks/");
    std::vector<std::string> track_names;
    Game_engine::load_txt(GAME_FOLDER+ TRACKS_FOLDER+"List.txt", track_names);
    m_track_->load(GAME_FOLDER + TRACKS_FOLDER + track_names[0]+".bmp");
  }
}//G6037599