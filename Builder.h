#pragma once

#include "ResourcesComponent.h"
#include "Building.h" 
#include "Field.h"
#include "Storage.h"

namespace structropolis
{
  class Builder
  {
  protected:
    std::string name_;
    const ResourcesComponent cost_;


  public:
    Builder(const std::string& name, const uint32_t gold, const uint32_t wood, const uint32_t stone, const uint32_t steel)
      : name_(name), cost_(gold, wood, stone, steel)
    {
    }

    virtual Building* Build(const Size2 p) = 0;

  protected:
    bool CheckCell(const Size2 p)
    {

    }
  };

  class MiningBuilder : public Builder
  {
  private:
    const uint32_t time_;
    const ResourcesComponent production_;


  public:
    MiningBuilder(const std::string& name, const uint32_t c_gold, const uint32_t c_wood, const uint32_t c_stone, const uint32_t c_steel, const uint32_t gold, const uint32_t wood, const uint32_t stone, const uint32_t steel, const uint32_t time)
      :Builder(name, c_gold, c_wood, c_stone, c_steel), production_(gold, wood, stone, steel), time_(time)
    {
    }

    Building* Build(const Size2 p) override
    {
      auto& field = Field::GetInstance();
      auto& cell = field.GetMap().Get(p);
      auto& storage = Storage::GetInstance();
      auto storage_sources = storage.GetComponent<ResourcesComponent>();
      auto resources = GetMin(*cell.GetComponent<ResourcesComponent>(), production_);
      if (cell.GetChild() != nullptr || *storage_sources < cost_ ||  resources.AreEmpty())
      {
        return nullptr;
      }

      *storage_sources -= cost_;

      auto building = new MiningBuilding(time_);      
      field.GetMap().Get(p).AddChild(building);

      building->AddComponent<ResourcesComponent>(resources);
      auto animator_ = building->AddComponent<AnimationComponent>(std::initializer_list<std::pair<std::string, Animation>>{
        {"Work", drawing::Animation{drawing::Sprite::LoadFromFile(name_), AnimationCurve{ {{0, 15}, {1, 15}, {2, 15}} }}},
        {"Produced", drawing::Animation{drawing::Sprite::LoadFromFile(name_), AnimationCurve{ {{3, 7}, {4, 7}, {3, 7}} }}},
      });

      animator_->GetAnimationList().GetValue("Produced")->OnAnimationEnd.Connect(building->on_animation_end_function);
      building->OnProduced.Connect(storage.on_produced_function);

      auto position_ = building->AddComponent<PositionComponent>(building->GetParent()->GetComponent<PositionComponent>()->GetPos());
      animator_->GetAnimationList().GetValue("Work")->GetSprite().GetMask().GetRect().SetPos(position_->GetPos());
      animator_->GetAnimationList().GetValue("Produced")->GetSprite().GetMask().GetRect().SetPos(position_->GetPos());
      animator_->PlayAnimation("Work");

      return building;
    }
  };

  class SupportBuilding : public Builder
  {
  private:
    const float multiplier_;

  public:
    SupportBuilding(const std::string& name, const uint32_t c_gold, const uint32_t c_wood, const uint32_t c_stone, const uint32_t c_steel, const float multiplier_)
      : Builder(name, c_gold, c_wood, c_stone, c_steel), multiplier_(multiplier_)
    {
    }

    Building* Build(const Size2 p) override
    {
      auto building = new Building();

      return building;
    }
  };
}
