#pragma once

#include "RealEngine.h"
#include "ResourcesComponent.h"

namespace structropolis
{
  class Storage : public GameObject, public Singleton<Storage>
  {
    friend class Singleton<Storage>;
  public:
    std::function<void(ResourcesComponent)> on_produced_function;

  private:
    ResourcesComponent* resources_;

  protected:
    Storage()
    {
      resources_ = AddComponent<ResourcesComponent>();
      on_produced_function = [this](const ResourcesComponent production)
      {
        *resources_ += production;
      };
    }

    ~Storage() override = default;
  };
}

