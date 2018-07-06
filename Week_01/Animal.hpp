#ifndef G6037599_ANIMAL_HPP
#define G6037599_ANIMAL_HPP
#pragma once

namespace G6037599
{
  class Animal
  {
  public:
    Animal();
    virtual ~Animal() = default;
    Animal(const Animal& t_to_copy) = default;
    Animal(Animal&& t_to_move) noexcept = default;
    Animal& operator = (const Animal& t_to_copy) = default;
    Animal& operator = (Animal&& t_to_move) noexcept = default;

    virtual void say();

    void set_age(int);
  private:
    int m_age_;
  };

  void demo_oop();
}//G6037599

#endif //G6037599_ANIMAL_HPP