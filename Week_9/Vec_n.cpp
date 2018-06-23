#include "stdafx.h"
#include "Vec_n.hpp"

namespace G6037599
{
  //___ public _______________________________________________________
  double Vec_n::size() const
  {
    return std::sqrt(squared_size());
  }
}//G6037599