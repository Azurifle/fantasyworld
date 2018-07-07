#include "stdafx.h"
#include "Screen_saver.hpp"
#include "Star.hpp"
#include "App.hpp"

namespace G6037599
{
  // ___ static ___________________________________________________________
  void Screen_saver::start()
  {
    static auto is_running = false;
    REQUIRE(!is_running);
    is_running = true;

    const auto WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
    App app(WINDOW_WIDTH, WINDOW_HEIGHT, "Screen Saver: Blinking Star");
    app.run();

    is_running = false;
  }

  // ___ private static ______________________________________________________
  Screen_saver Screen_saver::m_instance_{};

  // ___ private constructor ___________________________________________________
  Screen_saver::Screen_saver()
  {
    const auto STARS = 1;
    m_stars_.resize(STARS);
  }

  // ___ private ________________________________________________________________
  void Screen_saver::update()
  {
    m_delta_time_.reset();
    m_stars_[0].update(m_delta_time_.float_seconds());
  }
}//G6037599