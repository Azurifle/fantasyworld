#ifndef G6037599_LOGGER_HPP
#define G6037599_LOGGER_HPP
#pragma once

namespace G6037599
{
  class Logger final
  {
  public:
    static Logger& get_instance();//Singleton Lazy version

    ~Logger() = default;

    void log(const std::string& t_message);
  private:
    int m_count_;

    Logger();
    Logger(const Logger& t_to_copy) = default;
    Logger(Logger&& t_to_move) noexcept = default;
    Logger& operator = (const Logger& t_to_copy) = default;
    Logger& operator = (Logger&& t_to_move) noexcept = default;
  };
  
  void logger_demo();
}//G6037599

#endif //G6037599_LOGGER_HPP