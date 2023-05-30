#pragma once

#include <type_traits>

#include "Component.h"

namespace my_game::gameplay::base {

  class ComponentHasher {
  public:
    template<class T>
      requires std::is_base_of_v<IComponent, T>
    std::size_t operator()(const T& key) const
    {
      return typeid(key).hash_code();
     
    }

    template<class T>
      requires std::is_base_of_v<IComponent, T>
    std::size_t operator()() const
    {
      return typeid(T).hash_code();
    }
  };

}

