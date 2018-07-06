#ifndef G6037599_STOPWATCH_HPP
#define G6037599_STOPWATCH_HPP
#pragma once

namespace G6037599
{
  class Stopwatch final
  {
  public:
    using Elapsed = std::chrono::milliseconds;

    static void demo();

    Stopwatch();
    ~Stopwatch() = default;
    Stopwatch(const Stopwatch& t_to_copy) = default;
    Stopwatch(Stopwatch&& t_to_move) noexcept = default;
    Stopwatch& operator = (const Stopwatch& t_to_copy) = default;
    Stopwatch& operator = (Stopwatch&& t_to_move) noexcept = default;

    void restart();
    Elapsed stop() const;
  private:
    using Clock = std::chrono::high_resolution_clock;
    std::chrono::steady_clock::time_point m_start_time_{};
  };
}//G6037599

#endif //G6037599_STOPWATCH_HPP