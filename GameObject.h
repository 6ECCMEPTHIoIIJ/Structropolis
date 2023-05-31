#pragma once

#include "ComponentHasher.h"
#include "Container.h"

#include <ranges>

namespace re::gameplay::base
{

  class GameObject
  {
  private:
    static ComponentHasher hasher_;
    sources::Container<std::size_t, IComponent*> components_;
    GameObject* child_ = nullptr;
    GameObject* parent_ = nullptr;

  public:

    virtual ~GameObject()
    {
      for (auto& component : components_ | std::ranges::views::values)
      {
        delete component;
        component = nullptr;
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
    constexpr T* AddComponent(Args... args)
    {
      T* component = new T(args...);
      components_.Add(hasher_.operator() < T > (), component);

      return component;
    }

    template<class T>
      requires std::is_base_of_v<IComponent, T>
    void RemoveComponent()
    {
      delete GetComponent<T>();
      components_.Remove(hasher_.operator() < T > ());
    }

    void CreateChild()
    {
      child_ = new GameObject();
    }

    GameObject* AddChild(GameObject* child)
    {
      child_ = child;
      child_->parent_ = this;
    }

    GameObject* RemoveChild()
    {
      auto t = child_;
      child_->parent_ = nullptr;
      child_ = nullptr;

      return t;
    }

    GameObject* GetChild()
    {
      return child_;
    }

    GameObject* GetParent()
    {
      return parent_;
    }

    const GameObject* GetChild() const
    {
      return child_;
    }

    const GameObject* GetParent() const
    {
      return parent_;
    }
  };

  ComponentHasher GameObject::hasher_;
}

