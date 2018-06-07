#ifndef G6037599_CAT_HPP
#define G6037599_CAT_HPP
#pragma once
#include "Animal.hpp"

namespace G6037599
{
  class Cat : public Animal
  {
  public:
    Cat() = default;
    ~Cat() = default;
    Cat(const Cat& t_to_copy) = default;
    Cat(Cat&& t_to_move) noexcept = default;
    Cat& operator = (const Cat& t_to_copy) = default;
    Cat& operator = (Cat&& t_to_move) noexcept = default;

    void say() override;
  };
}//G6037599

#endif //G6037599_CAT_HPP