#pragma once

#include <functional>
#include "Rgb.h"

namespace my_game::drawing {

  class RgbHasher {
  public:
    std::size_t operator()(const core::Rgb& key) const
    {
      using std::size_t;
      using std::hash;

      return (hash<int>()(key.GetR())
        ^ (hash<int>()(key.GetG()) << 1)
        ^ (hash<int>()(key.GetB()) << 2));
    }
  };

}
