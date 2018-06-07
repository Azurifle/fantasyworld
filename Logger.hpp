#ifndef LOGGER
#define LOGGER
#pragma once

namespace G6037599
{
  class Logger
  {
  public:
    Logger();
    ~Logger() = default;

    void log(const char* t_message);
    static std::shared_ptr<Logger> share_instance();
  private:
    int m_count_;
  };
}//G6037599

#endif //CONSOLE