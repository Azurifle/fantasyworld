#include "stdafx.h"
#include "Logger.hpp"

namespace G6037599
{
  Logger::Logger() : m_count_(0) {}

  void Logger::log(const char* t_message)
  {
    ++m_count_;
    std::cout << m_count_  << " times, " << t_message << std::endl;
  }

  std::shared_ptr<Logger> Logger::share_instance()
  {
    static auto logger = std::make_shared<Logger>();
    return logger;
  }

}//G6037599