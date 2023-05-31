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
    Size2 old_pos_ = Size2::kZero;
    std::function<void(Size2)> on_position_changed_;

  public:
    explicit Field(const Map& map) :
      map_(map),
      position_component_(AddComponent<PositionComponent>(Size2::kZero))
    {
      on_position_changed_ = [this](const Size2 p)
      {
        auto delta = Vector2<int16_t>(
          p.GetX() - old_pos_.GetX(),
          p.GetY() - old_pos_.GetY());
        old_pos_ = p;
        for (auto& cell : map_)
        {
          auto cell_pos = cell.GetComponent<PositionComponent>();
          cell_pos->SetPos({ 
            static_cast<uint16_t>(cell_pos->GetPos().GetX() + delta.GetX()),
            static_cast<uint16_t>(cell_pos->GetPos().GetY() + delta.GetY()) });
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