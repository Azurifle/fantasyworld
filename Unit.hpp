#ifndef UNIT
#define UNIT
#pragma once

namespace G6037599
{
  class Unit
  {
  public:
    static const int NOT_ASSIGN = -1;

    virtual const char* get_name() const = 0;
    virtual int get_max_hp() const = 0;

    Unit() = default;
    virtual ~Unit() = default;

    virtual void damaged(int t_damage) = 0;
    virtual void print() const = 0;
  protected:
    int hp_ = NOT_ASSIGN;
  };
}

#endif //UNIT
