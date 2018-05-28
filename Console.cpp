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
  const int POP_UP_PANEL_WIDTH = 65;

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

  void Console::print_centered_text(const int t_width, const char* t_message, const char t_delim)
  {
    const auto SPACE_BEFORE = (t_width - std::strlen(t_message)) / 2
      , SPACE_AFTER = SPACE_BEFORE + SPACE_BEFORE % 2;
    std::cout << std::setw(SPACE_BEFORE) << std::setfill(t_delim);
    std::cout << t_message << std::setw(SPACE_AFTER) << std::setfill(t_delim);
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

    const short TO_PLAYER_HP_BAR = 3;
    cursor.X += static_cast<short>(m_timer_->WIDTH) + TO_PLAYER_HP_BAR;
    m_player_hp_ = std::make_unique<Hp_bar>(cursor);

    const short TO_CURSOR_STATUS_COLUMN = 3, TO_CURSOR_STATUS_ROW = 11;
    cursor.X = static_cast<short>(Map::SIZE) * static_cast<short>(SPACE_BETWEEN_TILE) + TO_CURSOR_STATUS_COLUMN;
    cursor.Y += TO_CURSOR_STATUS_ROW;
    m_cursor_status_ = std::make_unique<Status_panel>(cursor);

    m_pop_up_panel_cursor_ = find_map_cursor_pos({ Map::MIDDLE / 2, Map::MIDDLE / 2 });
    cursor = m_pop_up_panel_cursor_;
    
    const auto SPACE_BEFORE = (POP_UP_PANEL_WIDTH - std::strlen(GAME_RESET_MESSAGE)) / 2
      , SPACE_AFTER = SPACE_BEFORE + SPACE_BEFORE % 2;
    const auto GAME_RESET_ROW = 4, BACK_TO_COUNT_DOWN_NUM = 1;
    m_game_reset_count_down_cursor_ = COORD{ cursor.X - SPACE_AFTER - BACK_TO_COUNT_DOWN_NUM
      , cursor.Y + GAME_RESET_ROW };
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
    m_player_hp_->set(World::PLAYER_MAX_HP, World::PLAYER_MAX_HP);
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

  void Console::marked(const COORD& t_pos, const char* t_symbol, const bool t_is_attacker) const
  {
    REQUIRE(0 <= t_pos.X && t_pos.X < Map::SIZE);
    REQUIRE(0 <= t_pos.Y && t_pos.Y < Map::SIZE);

    switch (t_is_attacker)
    {
    case false: set_cursor(find_map_cursor_pos(t_pos));
      const auto SLOT_SIZE = 2;
      REQUIRE(std::strlen(t_symbol) <= SLOT_SIZE); break;
    default: const auto SLOT_ATTACKER = 1;
      REQUIRE(std::strlen(t_symbol) <= SLOT_ATTACKER);
      set_cursor(COORD{ find_map_cursor_pos(t_pos).X+ SLOT_ATTACKER
        , find_map_cursor_pos(t_pos).Y });
    }
    std::cout << t_symbol;

    set_cursor(m_player_cursor_);
  }

  void Console::move_player_cursor(const COORD& t_pos)
  {
    REQUIRE(0 <= t_pos.X && t_pos.X < Map::SIZE);
    REQUIRE(0 <= t_pos.Y && t_pos.Y < Map::SIZE);

    m_player_cursor_ = find_map_cursor_pos(t_pos);
    set_cursor(m_player_cursor_);
  }

  int Console::update_minute() const
  {
    const int result = m_timer_->update_minute();
    set_cursor(m_player_cursor_);
    return result;
  }

  bool Console::update_hour() const
  {
    const bool result = m_timer_->update_hour();
    set_cursor(m_player_cursor_);
    return result;
  }

  void Console::hide_cursor_status() const
  {
    m_cursor_status_->hide();//keep bool alreay hide or not
    set_cursor(m_player_cursor_);
  }

  void Console::update_cursor_status(const char* t_name, int t_hp, int t_max_hp, int t_atk, int t_max_atk) const
  {
    m_cursor_status_->show(t_name, t_hp, t_max_hp, t_atk, t_max_atk);
    set_cursor(m_player_cursor_);
  }

  void Console::thanks_user()
  {
    puts("");
    puts("");
    puts("");
    puts("                      ////////////////////// Rich Fantasy World ///////////////////");
    puts("");
    puts("                                       By: Darlyn Sirikasem G6037599.");
    puts("");
    puts("");
    puts("                                     THANK YOU FOR PLAYING THIS GAME !!!");
    puts("");
    puts("");
    puts("                      ////////////////////////////////////////////////////////////");
    puts("");
    puts("");
    puts("   Press <Any key> = exit ");
  }

  void Console::show_game_reset() const
  {
    auto cursor = m_pop_up_panel_cursor_;
    set_cursor(cursor);

    std::cout << std::setw(POP_UP_PANEL_WIDTH) << std::setfill('/');
    ++cursor.Y;
    set_cursor(cursor);

    std::cout << std::setw(POP_UP_PANEL_WIDTH) << std::setfill(' ');
    ++cursor.Y;
    set_cursor(cursor);

    print_centered_text(POP_UP_PANEL_WIDTH,
      (std::string("\" ") + World::PLAYER_NAME + std::string(" \" has fallen.")).c_str()
      , ' ');
    ++cursor.Y;
    set_cursor(cursor);

    std::cout << std::setw(POP_UP_PANEL_WIDTH) << std::setfill(' ');
    ++cursor.Y;
    set_cursor(cursor);

    print_centered_text(POP_UP_PANEL_WIDTH, GAME_RESET_MESSAGE, ' ');
    ++cursor.Y;
    set_cursor(cursor);

    std::cout << std::setw(POP_UP_PANEL_WIDTH) << std::setfill(' ');
    ++cursor.Y;
    set_cursor(cursor);

    std::cout << std::setw(POP_UP_PANEL_WIDTH) << std::setfill('/');
  }

  void Console::show_game_reset(const int t_count_down) const
  {
    set_cursor(m_game_reset_count_down_cursor_);
    std::cout << t_count_down;
  }

  void Console::set_player_full_hp() const
  {
    m_player_hp_->set(World::PLAYER_MAX_HP, World::PLAYER_MAX_HP);
  }

  void Console::set_player_hp(const int t_hp) const
  {
    REQUIRE(0 <= t_hp && t_hp <= World::PLAYER_MAX_HP);

    m_player_hp_->set(t_hp, World::PLAYER_MAX_HP);
    set_cursor(m_player_cursor_);
  }

  //___ private _______________________________________________________
  COORD Console::find_map_cursor_pos(const COORD& t_pos) const
  {
    REQUIRE(0 <= t_pos.X && t_pos.X < Map::SIZE);
    REQUIRE(0 <= t_pos.Y && t_pos.Y < Map::SIZE);

    return COORD{ m_map_start_.X + t_pos.X * SPACE_BETWEEN_TILE, m_map_start_.Y + t_pos.Y };
  }

}//G6037599
