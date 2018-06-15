#include "stdafx.h"
#include "Game_engine.hpp"
#include "1._Fantasy_Game/Fantasy_game.hpp"
#include "2._Car_Game/Car_game.hpp"

namespace G6037599
{
  //___ static ___________________________________________________________
  void Game_engine::start()
  {
    REQUIRE(!m_is_running_);
    m_is_running_ = true;

    disable_mouse_editing();
    srand(GetTickCount());

    while (true)
    {
      show_header();
      const char OPTION_1 = '1', OPTION_LAST = '2', ESC = 27;
      std::cout << "Press <" << OPTION_1 << " - " << OPTION_LAST << "> or [ESC] to exit: ";
      auto wrong_input = true;
      while (wrong_input)
      {
        switch (get_key())
        {
        case OPTION_1: system("CLS");
          Fantasy_game::run();
          wrong_input = false;
          back_to_main_menu();
          break;
        case OPTION_LAST: system("CLS");
          Car_game::run();
          wrong_input = false;
          back_to_main_menu();
          break;

        case ESC: puts("\n");
          puts("============================ End of Program ====================================");
          wait_key();
          m_is_running_ = false;
          return;
        default:;
        }
      }//input loop
    }//menu loop
  }

  bool Game_engine::is_running() { return m_is_running_; }

  int Game_engine::get_key()
  {
    switch (_kbhit())
    {
    case KEY_NO_PRESS: return KEY_NO_PRESS;
    default: return wait_key();
    }//switch 1st keyboard hit
  }

  int Game_engine::wait_key()
  {
    const auto FIRST_KEY = _getch();
    switch (FIRST_KEY)
    {
    case KEY_ARROW: return _getch();
    default: switch (_kbhit())
      {
      case KEY_NO_PRESS: break;
      default: _getch();
      }//switch 2nd keyboard hit
      return FIRST_KEY;
    }
  }

  int Game_engine::wait_key(const int t_miliseconds)
  {
    const auto TIME_UP = clock() + t_miliseconds;
    do
    {
      const auto KEY = get_key();
      switch (KEY)
      {
      case KEY_NO_PRESS: break;
      default: return KEY;
      }

      Sleep(FPS_50);
    } while (clock() < TIME_UP);

    return KEY_NO_PRESS;
  }

  short Game_engine::limit_interval(const short t_number, const short t_min, const short t_max)
  {
    if (t_number <= t_min)
    {
      return t_min;
    }
    if (t_number >= t_max)
    {
      return t_max;
    }
    return t_number;
  }

  void Game_engine::load_txt(const std::string& t_path, std::vector<std::string>& t_tokens_out)
  {
    std::ifstream file_reader(t_path);
    REQUIRE(file_reader.is_open());//should change to popup warning later

    std::string temp;
    while (std::getline(file_reader, temp))
    {
      const auto TAB = '\t';
      std::istringstream string_cutter(temp);
      while(std::getline(string_cutter, temp, TAB))
      {
        t_tokens_out.push_back(temp);
      }
    }
    file_reader.close();
  }

  int Game_engine::find_elapsed_milisec()
  {
    static auto last_milisec = clock();

    const int ELAPSED = clock() - last_milisec;
    last_milisec = clock();
    return ELAPSED;
  }

  COORD Game_engine::get_cursor()
  {
    CONSOLE_SCREEN_BUFFER_INFO console_info;
    PROMISE(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &console_info));
    return console_info.dwCursorPosition;
  }

  /*char Game_engine::get_cursor_char()
  {
    const LPWSTR CHAR_OUT = nullptr;
    if(ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE)
      , CHAR_OUT, 1, get_cursor(), nullptr))
    {
      return static_cast<char>(*CHAR_OUT);
    }
    return ' ';
  }*/

  void Game_engine::set_cursor(const COORD& t_coord)
  {
    REQUIRE(0 <= t_coord.X); REQUIRE(t_coord.X <= CMD_LAST_COLS);
    REQUIRE(0 <= t_coord.Y); REQUIRE(t_coord.Y <= CMD_LAST_ROWS);

    PROMISE(SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), t_coord));
  }

  //___ private static ___________________________________________________________
  bool Game_engine::m_is_running_ = false;

  void Game_engine::disable_mouse_editing()
  {
    DWORD prev_mode;
    PROMISE(GetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), &prev_mode));
    PROMISE(SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), prev_mode & ~ENABLE_QUICK_EDIT_MODE));
  }

  void Game_engine::show_header()
  {
    puts("=== Game Engine =======================");
    puts("");
    puts("By: Darlyn Sirikasem G6037599");
    puts("");
    puts("");
    puts("         ////////////////////////// Game list /////////////////////////////");
    puts("");
    puts("                    1. The Fantasy World - NoOne The Hero.");
    puts("");
    puts("                    2. Bit Autonomous Car.");
    puts("");
    puts("         //////////////////////////////////////////////////////////////////");
    puts("");
    puts("");
  }

  void Game_engine::back_to_main_menu()
  {
    std::cout << std::endl
      << "Press <Any key> to main menu: ";
    _getch(); _getch();
    system("CLS");
  }
}//G6037599