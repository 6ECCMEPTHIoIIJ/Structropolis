#pragma once

#include "ResourcesComponent.h"
#include "Building.h" 
#include "Field.h"

namespace structropolis
{
  class Builder
  {
  protected:
    std::string name_;

  public:
    Builder(const std::string& name)
      : name_(name)
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
    
    const uint32_t gold_;
    const uint32_t wood_;
    const uint32_t stone_;
    const uint32_t steel_;

  public:
    MiningBuilder(const std::string& name,  const uint32_t gold, const uint32_t wood, const uint32_t stone, const uint32_t steel)
      :Builder(name), gold_(gold), wood_(wood), stone_(stone), steel_(steel)
    {
    }

    Building* Build(const Size2 p) override
    {
      auto building = new Building();
      building->AddComponent<ResourcesComponent>(gold_, wood_, stone_, steel_);
      building->AddComponent<AnimationComponent>(std::initializer_list<std::pair<std::string, Animation>>{
        {"_", drawing::Animation{drawing::Sprite::LoadFromFile(name_)}},
      });
      building->AddComponent<PositionComponent>();



      auto& field = Field::GetInstance();
      field.GetMap().Get(p).AddChild(building);

      building->GetParent()->GetComponent<PositionComponent>()->GetPos();

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
