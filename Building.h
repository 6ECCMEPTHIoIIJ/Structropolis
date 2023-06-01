#pragma once

#include "RealEngine.h"
#include "ResourcesComponent.h"

namespace structropolis
{
  class Building : public GameObject
  {

  };

  class MiningBuilding : public Building
  {
  public:
    Signal<void(ResourcesComponent)> OnProduced;
    std::function<void(ResourcesComponent)> on_produces_function;
    std::function<void()> on_animation_end_function;

  public:
    MiningBuilding(const uint32_t &time)
    {
      on_animation_end_function = [this]()
      {
        GetComponent<AnimationComponent>()->PlayAnimation("Work");
      };

      std::jthread([&]
        {
          while (true)
          {
            std::this_thread::sleep_for(std::chrono::milliseconds(time));
            if (GetComponent<ResourcesComponent>() != nullptr)
            {
              GetComponent<AnimationComponent>()->PlayOneShotAnimation("Produced");
              OnProduced.Notify(*GetComponent<ResourcesComponent>());
            }
          }
        }).detach();
    }

  };
}


