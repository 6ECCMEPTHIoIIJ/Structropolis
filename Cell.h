#pragma once

#include "RealEngine.h"
#include "PositionComponent.h"
#include "ResourcesComponent.h"

namespace structropolis
{

  class Cell : public GameObject
  {
  private:
    const PositionComponent* position_component_;
    AnimationComponent* animator_;
    const ResourcesComponent* resources_;


  public:
    Cell(const Size2& p, const char ch) : Cell(p,
      (ch == 'f' || ch == 'F' ? "ForestCell", ResourcesComponent(0, 30, 0, 0) :
      ch == 't' || ch == 'T' ? "ForestCell", ResourcesComponent(0, 0, 20, 0) :
      ch == 's' || ch == 'S' ? "ForestCell", ResourcesComponent(0, 0, 20, 10) : "ForestCell", ResourcesComponent(0, 0, 0, 0)))
    {
    }

    Cell(const Size2& p, const std::string& sprite_name, const ResourcesComponent& resources) : Cell(p, sprite_name,
      resources.GetGold(), resources.GetWood(), resources.GetStone(), resources.GetSteel())
    {
    }

    Cell(const Size2& p, const std::string& sprite_name, const Gold gold, const Wood wood, const Stone stone, const Steel steel) :
      Cell(p, sprite_name, gold.GetValue(), wood.GetValue(), stone.GetValue(), steel.GetValue())
    {

    }

    Cell(const Size2& p, const std::string& sprite_name, const uint32_t gold, const uint32_t wood, const uint32_t stone, const uint32_t steel) :
      position_component_(AddComponent<PositionComponent>(p)),
      animator_(AddComponent<AnimationComponent>(std::initializer_list<std::pair<std::string, re::drawing::Animation>>{
        {"_", Animation{ Sprite::LoadFromFile(sprite_name) }}})),
      resources_(AddComponent<ResourcesComponent>(gold, wood, stone, steel))
    {
      animator_->GetAnimationList().GetValue("_")->GetSprite().SetPos(p);
    }

    void Draw()
    {
      animator_->PlayAnimation("_");
    }
  };
}

