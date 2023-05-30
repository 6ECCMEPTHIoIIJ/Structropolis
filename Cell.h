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

