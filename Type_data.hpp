#ifndef TYPE_DATA
#define TYPE_DATA
#pragma once

namespace G6037599
{
  class Type_data
  {
  public:
    const std::string NAME{}, DEAD_MESSAGE{}, ATK_NAME{};
    const int ATK = 0, MAX_ATK = 0, ORIGIN_MAX_HP = 0;
    const char SYMBOL = 'U';

    Type_data(const std::string& t_name
      , const std::string& t_dead_message
      , const std::string& t_atk_name
      , int t_max_hp, int t_atk, int t_max_atk, char t_symbol);
    ~Type_data() = default;
    Type_data(const Type_data& t_to_copy) = default;
    Type_data& operator=(const Type_data& t_to_copy);

    int get_max_hp() const;
    void increase_max_hp(int t_amount);
    int random_atk() const;
    void reset_max_hp();
  private:
    int m_max_hp_ = 0;
  };
}

#endif //TYPE_DATA
