#ifndef TYPE_DATA
#define TYPE_DATA
#pragma once

namespace G6037599
{
  class Type_data
  {
  public:
    const char* NAME = "", *DEAD_MESSAGE = "", *ATK_NAME = "";
    const int ATK = 0, MAX_ATK = 0;
    const char SYMBOL = 'U';

    Type_data(const char* t_name, const char* t_dead_message, const char* t_atk_name
      , int t_max_hp, int t_atk, int t_max_atk, char t_symbol);
    ~Type_data() = default;
    Type_data(const Type_data& t_to_copy) = default;
    Type_data& operator=(const Type_data& t_to_copy);

    int get_max_hp() const;
    void increase_max_hp(int t_amount);
    int random_atk() const;
  private:
    int m_max_hp_ = 0;
  };
}

#endif //TYPE_DATA
