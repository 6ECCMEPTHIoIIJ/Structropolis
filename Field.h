#pragma once

#include "RealEngine.h"
#include "Map.h"
#include "MapLoader.h"

namespace structropolis
{
  class Field : public GameObject
  {
  private:
    PositionComponent* position_component_;
    Map map_;

    std::function<void(Size2)> on_position_changed_;

  public:
    explicit Field(const Map& map) : 
      map_(map), 
      position_component_(AddComponent<PositionComponent>(Size2::kZero))
    {
      on_position_changed_ = [this](const Size2 p)
      {
        Size2 delta = p - position_component_->GetPos();
        for (auto& cell : map_)
        {
          auto cell_pos = cell.GetComponent<PositionComponent>();
          cell_pos->SetPos(cell_pos->GetPos() + delta);
        }
      };

      position_component_->OnPositionChanged.Connect(on_position_changed_);
    }

    void Draw()
    {
      for (auto& cell : map_)
      {
        cell.Draw();
      }
    }

    static Field LoadFromFile(const std::string& name)
    {
      auto& map_loader = MapLoader::GetInstance();
      return Field(map_loader.LoadFormFile(name));
    }
  };
}