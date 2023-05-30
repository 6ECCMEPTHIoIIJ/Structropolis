#pragma once

#include "GameObject.h"
#include "PositionComponent.h"

namespace structropolis
{

  class Cell : public re::gameplay::base::GameObject
  {
  private:
    PositionComponent* position_component_;

  public:
    Cell(const re::utility::Size2& p)
    {
      position_component_ = AddComponent<PositionComponent>(p);
    }
  };
}

