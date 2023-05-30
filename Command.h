#pragma once

#include "RealEngine.h"
#include "Building.h"

namespace structropolis
{
  class Command
  {
  public:
    virtual void Execute() = 0;
  };

  class BuildCommand : public Command
  {
  private:
    Size2 position_;
    Building* building_;

  public:

    BuildCommand(const Size2 position_, Building* building_)
      : position_(position_), building_(building_)
    {
    }
  };
}

