#ifndef STOPWATCH
#define STOPWATCH
#pragma once

namespace G6037599
{
  class Stopwatch
  {
  public:
    const typedef std::chrono::high_resolution_clock clock;
    const typedef std::chrono::milliseconds elapsed;

    static std::shared_ptr<Stopwatch> share_instance();

    Stopwatch() = default;
    ~Stopwatch() = default;

    void start();
    elapsed stop() const;
  private:
    std::chrono::steady_clock::time_point m_t1_, m_t2_;
  };
}//G6037599

#endif //STOPWATCH