#pragma once

#include "Component.h"
#include "Size2.h"

namespace structropolis
{
  class PositionComponent : public re::gameplay::base::IComponent
  {
  private:
    re::utility::Size2 position_;

  public:
    explicit PositionComponent(const re::utility::Size2& position)
      : position_(position)
    {
    }

    [[nodiscard]]
    re::utility::Size2 GetPos() const
    {
      return position_;
    }

    void SetPos(const re::utility::Size2& p)
    {
      position_ = p;
    }
  };
}

