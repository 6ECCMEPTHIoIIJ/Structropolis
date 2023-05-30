#pragma once

#include "ComponentHasher.h"
#include "Container.h"

namespace re::gameplay::base
{

  class GameObject
  {
  private:
    ComponentHasher hasher_;
    sources::Container<std::size_t, IComponent*> components_;

  public:
    virtual ~GameObject()
    {
      for (auto& component : components_ | std::views::values)
      {
        delete component;
      }
    }

    template<class T>
      requires std::is_base_of_v<IComponent, T>
    T* GetComponent()
    {
      if (!components_.Has(hasher_.operator() < T > ()))
      {
        return nullptr;
      }

      return dynamic_cast<T*>(*components_.GetValue(hasher_.operator() < T > ()));
    }

    template<class T, class ...Args>
      requires std::is_base_of_v<IComponent, T>
    T* AddComponent(Args... args)
    {
      T* component = new T(args...);
      components_.Add(hasher_.operator() < T > (), component);

      return component;
    }

    template<class T>
      requires std::is_base_of_v<IComponent, T>
    void RemoveComponent()
    {
      components_.Remove(hasher_.operator() < T > ());
    }
  };

}

