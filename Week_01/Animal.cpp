#include "stdafx.h"
#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

namespace G6037599
{
  //___ static _______________________________________________________
  void demo_oop()
  {
    Animal* animal = new Animal()
      , *dog = new Dog()
      , *cat = new Cat();

    animal->set_age(50);

    animal->say();
    dog->say();
    cat->say();

    delete animal;
    delete dog;
    delete cat;
  }

  //___ (de)constructors/operators ____________________________________
  Animal::Animal() : m_age_(0) {}

  //___ public _______________________________________________________
  void Animal::say()
  {
    puts("ZZZ");
  }

  void Animal::set_age(int t_age)//info hiding
  {
    if (t_age <= 0)
      t_age = 0;

    m_age_ = t_age;
  }
}//G6037599