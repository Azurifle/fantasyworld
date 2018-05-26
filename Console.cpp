#include "stdafx.h"
#include "Console.hpp"
#include "World.hpp"
#include "Map.hpp"
#include "Status_panel.hpp"
#include "Hp_bar.hpp"
#include "Timer.hpp"

namespace G6037599
{
  //___ static _______________________________________________________
  COORD Console::get_cursor()
  {
    CONSOLE_SCREEN_BUFFER_INFO console_info;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &console_info))
    {
      return console_info.dwCursorPosition;
    }
    const COORD ORIGIN = { 0, 0 };
    return ORIGIN;
  }

  void Console::set_cursor(const COORD& t_pos)
  {
    PROMISE(SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), t_pos));
  }

  //___ (de)constructors _____________________________________________
  Console::Console()
  {
    REQUIRE(std::strlen(World::PLAYER_NAME) <= Status_panel::MAX_NAME_LENGTH);
    const auto CMD_ROW_LIMIT = 40;
    REQUIRE(Map::SIZE < CMD_ROW_LIMIT);

    auto cursor = get_cursor();
    ++cursor.X;
    m_monster_status_ = std::make_unique<Status_panel>(cursor);

    const short FIRST_COLUMN = 0;
    m_map_start_ = { FIRST_COLUMN, cursor.Y + static_cast<short>(m_monster_status_->HIEGHT)};

    const short TO_TIMER_PANEL = 1;
    cursor.X += static_cast<short>(m_monster_status_->WIDTH) + TO_TIMER_PANEL;
    ++cursor.Y;
    m_timer_ = std::make_unique<Timer>(cursor);

    const short TO_PLAYER_HP_BAR = 3, PLAYER_MAX_HP = 50;
    cursor.X += static_cast<short>(m_timer_->WIDTH) + TO_PLAYER_HP_BAR;
    m_player_hp_ = std::make_unique<Hp_bar>(cursor);
    m_player_hp_->increase_max(PLAYER_MAX_HP);

    const short TO_CURSOR_STATUS_COLUMN = 3, TO_CURSOR_STATUS_ROW = 11;
    cursor.X = static_cast<short>(Map::SIZE) * static_cast<short>(SPACE_BETWEEN_TILE) + TO_CURSOR_STATUS_COLUMN;
    cursor.Y += TO_CURSOR_STATUS_ROW;
    m_cursor_status_ = std::make_unique<Status_panel>(cursor);

    show();
  }

  Console::Console(const Console& t_to_copy)
  {
    m_map_start_ = t_to_copy.m_map_start_;
    *m_monster_status_ = *t_to_copy.m_monster_status_;
    *m_cursor_status_ = *t_to_copy.m_cursor_status_;
    *m_player_hp_ = *t_to_copy.m_player_hp_;
    *m_timer_ = *t_to_copy.m_timer_;
  }

  Console& Console::operator=(const Console& t_to_copy)
  {
    m_map_start_ = t_to_copy.m_map_start_;
    *m_monster_status_ = *t_to_copy.m_monster_status_;
    *m_cursor_status_ = *t_to_copy.m_cursor_status_;
    *m_player_hp_ = *t_to_copy.m_player_hp_;
    *m_timer_ = *t_to_copy.m_timer_;
    return *this;
  }

  //___ public _______________________________________________________
  void Console::show() const
  {
    m_timer_->show();

    print_player_status();

    print_map();

    auto cursor = m_cursor_status_->get_pos();
    --cursor.Y;
    set_cursor(cursor);
    std::cout << "=== Cursor ===";

    const short TO_CURSOR_INSTRUCT = 2;
    cursor.Y += static_cast<short>(m_cursor_status_->HIEGHT) + TO_CURSOR_INSTRUCT;
    set_cursor(cursor);
    std::cout << "   [^]" << std::endl;
    std::cout << "[<][V][>] = move cursor";

    const short TO_WSAD_INSTRUCT_COLUMN = 15, TO_WSAD_INSTRUCT_ROW = 1;
    cursor = { m_map_start_.X + TO_WSAD_INSTRUCT_COLUMN
      , m_map_start_.Y + Map::SIZE + TO_WSAD_INSTRUCT_ROW };
    set_cursor(cursor);
    std::cout << "   [W]" << std::endl;
    std::cout << "[A][S][D] = move";

    const short TO_SPACE_INSTRUCT = 40;
    cursor.X += TO_SPACE_INSTRUCT;
    ++cursor.Y;
    set_cursor(cursor);
    std::cout << "[SPACE] = force update";

    const short TO_ESC_INSTRUCT = 5;
    cursor.X = Map::SIZE * SPACE_BETWEEN_TILE + TO_ESC_INSTRUCT;
    --cursor.Y;
    std::cout << "[ESC] = exit";
  }

  void Console::print_player_status() const
  {
    auto cursor = m_player_hp_->get_pos();
    enum Enum { BACK_TO_EDGE = 2, PLAYER_STATUS_WIDTH = 24 };
    cursor.X -= BACK_TO_EDGE;
    --cursor.Y;
    set_cursor(cursor);
    std::cout << "== \" " << World::PLAYER_NAME << " \" ==";

    ++cursor.Y;
    set_cursor(cursor);
    std::cout << '|';
    m_player_hp_->show();
    std::cout << " |";

    ++cursor.Y;
    set_cursor(cursor);
    std::cout << "| ATK: " << World::PLAYER_ATK << " - " << World::PLAYER_MAX_ATK;
    std::cout << std::setw(cursor.X + PLAYER_STATUS_WIDTH - get_cursor().X) << std::setfill(' ') << '|';

    ++cursor.Y;
    set_cursor(cursor);    
    std::cout << std::setw(PLAYER_STATUS_WIDTH) << std::setfill('=');
  }

  void Console::print_map() const
  {
    set_cursor(m_map_start_);
    for (int row = m_map_start_.X; row < Map::SIZE; ++row)
    {
      for (int column = m_map_start_.Y; column < Map::SIZE; ++column)
      {
        std::cout << " . ";
      }
      puts("");
    }
  }

}//G6037599
