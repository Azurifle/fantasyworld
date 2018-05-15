#ifndef PLAYER
#define PLAYER
#pragma once
#include "Unit.hpp"

namespace G6037599
{
  class Player : public Unit
  {
  public:
    int max_hp = NOT_ASSIGN;

    const char* get_name() const override;
    int get_max_hp() const override;

    Player(const char* t_name, int t_hp);

    void damaged(int t_damage) override;
    void print() const override;
  private:
    const char* m_name_ = nullptr;
    bool m_is_dead_ = false;
  };
}

#endif //PLAYER
