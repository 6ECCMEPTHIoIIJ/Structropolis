#pragma once

#include "ResourcesComponent.h"
#include "Building.h"

namespace structropolis
{
  class Builder
  {
  public:
    virtual Building* Build(const Size2 p) = 0;

  protected:
    bool CheckCell(const Size2 p)
    {

    }
  };

  class MiningBuilder : public Builder
  {
  private:
    const uint32_t gold_;
    const uint32_t wood_;
    const uint32_t stone_;
    const uint32_t steel_;

  public:
    MiningBuilder(const uint32_t gold, const uint32_t wood, const uint32_t stone, const uint32_t steel)
      : gold_(gold), wood_(wood), stone_(stone), steel_(steel)
    {
    }

    Building* Build(const Size2 p) override
    {
      auto building = new Building();
      building->AddComponent<ResourcesComponent>(gold_, wood_, stone_, steel_);

      return building;
    }
  };

  class SupportBuilding : public Builder
  {
  private:
    const float multiplier_;

  public:
    SupportBuilding(const float multiplier_)
      : multiplier_(multiplier_)
    {
    }

    Building* Build(const Size2 p) override
    {
      auto building = new Building();

      return building;
    }
  };
}
