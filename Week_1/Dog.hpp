#ifndef G6037599_DOG_HPP
#define G6037599_DOG_HPP
#pragma once
#include "Animal.hpp"

namespace G6037599
{
  class Dog : public Animal
  {
  public:
    Dog() = default;
    ~Dog() = default;
    Dog(const Dog& t_to_copy) = default;
    Dog(Dog&& t_to_move) noexcept = default;
    Dog& operator = (const Dog& t_to_copy) = default;
    Dog& operator = (Dog&& t_to_move) noexcept = default;

    void say() override;
  };
}//G6037599

#endif //G6037599_DOG_HPP