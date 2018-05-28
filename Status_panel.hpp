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

    COORD get_pos() const;
    void show(const char* t_name, int t_hp, int t_max_hp, int t_atk, int t_max_atk);
    void hide();
  private:
    COORD m_start_ = {0, 0};
    std::unique_ptr<Hp_bar> m_hp_ = nullptr;
    bool m_is_hide_ = true;
  };
}//G6037599

#endif //STATUS_PANEL

