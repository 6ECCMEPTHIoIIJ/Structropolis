#pragma once

#include <cstdint>
#include <cmath>

#include "RealEngine.h"
#include "Material.h"
#include "Product.h"

namespace structropolis
{
  class ResourcesComponent : public IComponent
  {
  private:
    uint32_t gold_ = 0;
    uint32_t wood_ = 0;
    uint32_t stone_ = 0;
    uint32_t steel_ = 0;

  public:
    ResourcesComponent()
    {
    }

    ResourcesComponent(const ResourcesComponent& other) :
      gold_(other.gold_), wood_(other.wood_), stone_(other.stone_), steel_(other.steel_)
    {

    }

    ResourcesComponent(const Gold gold, const Wood wood, const Stone stone, const Steel steel) :
      gold_(gold.GetValue()), wood_(wood.GetValue()), stone_(stone.GetValue()), steel_(steel.GetValue())
    {

    }

    ResourcesComponent(uint32_t gold, uint32_t wood, uint32_t stone, uint32_t steel)
      : gold_(gold), wood_(wood), stone_(stone), steel_(steel)
    {
    }

    bool AreEmpty() const
    {
      return gold_ == 0 &&
        wood_ == 0 &&
        stone_ == 0 &&
        steel_ == 0;
    }

    friend ResourcesComponent GetMin(const ResourcesComponent& left, const ResourcesComponent& right)
    {
      return {
        std::min(left.gold_, right.gold_),
        std::min(left.wood_, right.wood_),
        std::min(left.stone_, right.stone_),
        std::min(left.steel_, right.steel_)
      };
    }

    [[nodiscard]]
    Gold GetGold() const
    {
      return Gold(gold_);
    }

    [[nodiscard]]
    Wood GetWood() const
    {
      return Wood(wood_);
    }

    [[nodiscard]]
    Stone GetStone() const
    {
      return Stone(stone_);
    }

    [[nodiscard]]
    Steel GetSteel() const
    {
      return Steel(steel_);
    }

    void SetGold(const uint32_t gold)
    {
      gold_ = gold;
    }

    void SetWood(const uint32_t wood)
    {
      wood_ = wood;
    }

    void SetStone(const uint32_t stone)
    {
      stone_ = stone;
    }

    void SetSteel(const uint32_t steel)
    {
      steel_ = steel;
    }
  };
}

