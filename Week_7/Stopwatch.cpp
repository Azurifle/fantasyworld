#include "stdafx.h"
#include "Stopwatch.hpp"

namespace G6037599
{
  //___ static _______________________________________________________
  void Stopwatch::demo()
  {
    Stopwatch watch;
    std::cout << "Stopwatch has started. Press <Any key> to stop.";
    _getch();
    _getch();
    std::cout << std::endl
      << std::endl << "Time has elasped " << watch.stop().count() << " milliseconds." << std::endl;
  }

  //___ (de)constructors/operators ___________________________________
  Stopwatch::Stopwatch()
  {
    restart();
  }

  //___ public _______________________________________________________
  void Stopwatch::restart()
  {
    m_start_time_ = Clock::now();
  }

  Stopwatch::Elapsed Stopwatch::stop() const
  {
    return std::chrono::duration_cast<Elapsed>(Clock::now() - m_start_time_);
  }
}//G6037599