#ifndef STATUS_PANEL
#define STATUS_PANEL
#pragma once

namespace G6037599
{
  class Hp_bar;

  class Status_panel
  {
  public:
    const enum Enum 
    { 
      MAX_NAME_LENGTH = 14, HIEGHT = 4, WIDTH = 20/* [|||HP:999/999|||] */
    };

    explicit Status_panel(COORD t_pos);
    ~Status_panel() = default;
    Status_panel(const Status_panel& t_to_copy);
    Status_panel& operator=(const Status_panel& t_to_copy);

    void show() const;
    COORD get_pos() const;
  private:
    COORD m_start_ = {0, 0};
    std::string m_name_ = std::string("");
    std::unique_ptr<Hp_bar> m_hp_ = nullptr;
    int m_atk_ = 0, m_max_atk_ = 0;
  };
}//G6037599

#endif //STATUS_PANEL

