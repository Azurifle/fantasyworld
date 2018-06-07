#include "stdafx.h"
#include "Stopwatch.hpp"

namespace G6037599
{
  //___ static _______________________________________________________
  std::shared_ptr<Stopwatch> Stopwatch::share_instance()
  {
    static auto watch = std::make_shared<Stopwatch>();
    return watch;
  }

  //___ public _______________________________________________________
  void Stopwatch::start()
  {
    m_t1_ = clock::now();
  }

  Stopwatch::elapsed Stopwatch::stop() const
  {
    return std::chrono::duration_cast<Stopwatch::elapsed>(clock::now() - m_t1_).count();
  }
}//G6037599