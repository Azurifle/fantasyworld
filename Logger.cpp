#include "stdafx.h"
#include "Logger.hpp"

namespace G6037599
{
  //___ static _______________________________________________________
  void logger_demo()
  {
    Logger::get_instance().log("Hello I\'m \"Logger_demo\", and I\'m using logger to log this.");
    Logger::get_instance().log("Now I\'ll let world and monster log something.");

    class World final
    {
    public:
      World()
      {
        Logger::get_instance().log("World is created.");
      }
    };
    class Monster final
    {
    public:
      Monster()
      {
        Logger::get_instance().log("Monster is born.");
      }
    };

    World world;
    Monster monster;
  }

  Logger& Logger::get_instance()
  {
    static Logger instance;
    return instance;
  }

  //___ public _______________________________________________________
  void Logger::log(const std::string& t_message)
  {
    ++m_count_;
    std::cout << m_count_  << " times, " << t_message.c_str() << std::endl;
  }

  //___ private (de)constructors/operators __________________________
  Logger::Logger() : m_count_(0) {}
}//G6037599