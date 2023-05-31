#pragma once

#include "RealEngine.h"
#include "PositionComponent.h"
#include "ResourcesComponent.h"
#include "CellBase.h"

namespace structropolis
{
  class Cell : public CellBase
  {
  private:
    PositionComponent* position_component_;
    std::function<void(Size2)> on_position_changed_;


  public:
    Cell(const Size2 p, const char ch) : CellBase(ch), position_component_(AddComponent<PositionComponent>(p))
    {
      Initialize();
    }

    Cell(const Size2 p, const std::string& sprite_name, const uint32_t gold, const uint32_t wood, const uint32_t stone, const uint32_t steel) :
      CellBase(sprite_name, gold, wood, stone, steel), position_component_(AddComponent<PositionComponent>(p))
    {
      Initialize();
    }

    Cell(const Cell& other) : CellBase(other), position_component_(AddComponent<PositionComponent>(*other.position_component_))
    {
      Initialize();
    }

    void Draw()
    {
      animator_->PlayAnimation("_");
    }

    bool IsEmpty() const
    {
      return GetChild() == nullptr;
    }

  private:
    void Initialize()
    {
      animator_->GetAnimationList().GetValue("_")->GetSprite().SetPos(position_component_->GetPos());
      on_position_changed_ = [this](const Size2 p)
      {
        animator_->GetAnimationList().GetValue("_")->GetSprite().Clear();
        animator_->GetAnimationList().GetValue("_")->GetSprite().SetPos(p);
      };

      position_component_->OnPositionChanged.Connect(on_position_changed_);
    }
  };
}

