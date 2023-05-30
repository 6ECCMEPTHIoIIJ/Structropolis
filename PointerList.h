#pragma once

#include <vector>
#include <cstdint>

namespace my_game::sources {

  template<class T>
  class PointerList
    : public std::vector<T*> {
    using std::vector<T*>::vector;
    using Base = std::vector<T*>;

  public:
    [[nodiscard]]
  	T& Get(const uint16_t i)
    {
      return *Base::at(i);
    }

    [[nodiscard]] const T& Get(const uint16_t i) const
    {
      return *Base::at(i);
    }
  };

  template<class T>
  using ConstPointerList = PointerList<const T>;
}

