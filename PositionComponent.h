#pragma once

#include "RealEngine.h"
#include "Size2.h"

namespace structropolis
{
  class PositionComponent : public IComponent
  {
  private:
    Size2 position_;

  public:
    explicit PositionComponent(const Size2& position)
      : position_(position)
    {
    }

    [[nodiscard]]
    Size2 GetPos() const
    {
      return position_;
    }

    void SetPos(const Size2& p)
    {
      position_ = p;
    }
  };
}

