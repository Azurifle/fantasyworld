#include "stdafx.h"
#include "Logger.hpp"

namespace G6037599
{
  //___ static _______________________________________________________
  void logger_demo()
  {
    Logger::get_instance().log("Hello I\'m \"Logger_demo\", and I\'m using logger to log this.");
    Logger::get_instance().log("Now I\'ll let world and monster log something.");

    class Monster final
    {
    public:
      const int ID;

      Monster() : ID(1)
      {
        Logger::get_instance().log("Monster is born.");
      }
    };
    class World final
    {
    public:
      World() : m_id_(0)
      {
        Logger::get_instance().log("World is created.");
      }

      void add(const Monster& t_monster)
      {
        m_id_ = t_monster.ID;
      };

    private:
      int m_id_;
    };

    World world;
    const Monster monster;
    world.add(monster);
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