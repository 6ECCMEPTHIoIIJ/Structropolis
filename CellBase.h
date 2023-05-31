#pragma once

#include "RealEngine.h"
#include "ResourcesComponent.h"

namespace structropolis
{
  class CellBase : public GameObject
  {
  public:
    static constexpr Size2 kSize{5, 3};

    static const CellBase kForestCell;
    static const CellBase kStoneCell;
    static const CellBase kSteelCell;
    static const CellBase kEmptyCell;

  protected:
    AnimationComponent* animator_;
    const ResourcesComponent* resources_;

  public:
    CellBase(const char ch) : CellBase(
      ch == 'f' || ch == 'F' ? kForestCell :
      ch == 't' || ch == 'T' ? kStoneCell :
      ch == 's' || ch == 'S' ? kSteelCell : kEmptyCell)
    {
    }

    CellBase(const CellBase& other) :
      animator_(AddComponent<AnimationComponent>(*other.animator_)),
      resources_(AddComponent<ResourcesComponent>(*other.resources_))
    {
    }

    CellBase(const std::string& sprite_name, const uint32_t gold, const uint32_t wood, const uint32_t stone, const uint32_t steel) :
      animator_(AddComponent<AnimationComponent>(std::initializer_list<std::pair<std::string, re::drawing::Animation>>{
        {"_", Animation{ Sprite::LoadFromFile(sprite_name) }}})),
      resources_(AddComponent<ResourcesComponent>(gold, wood, stone, steel))
    {
    }

    void Draw()
    {
      animator_->PlayAnimation("_");
    }
  };

  const CellBase CellBase::kForestCell{"ForestCell", 0, 30, 0, 0};
  const CellBase CellBase::kStoneCell{"StoneCell", 0, 0, 20, 0};
  const CellBase CellBase::kSteelCell{"SteelCell", 0, 0, 0, 7};
  const CellBase CellBase::kEmptyCell{"EmptyCell", 0, 0, 0, 0};
}

