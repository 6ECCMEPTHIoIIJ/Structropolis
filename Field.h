#pragma once

#include "RealEngine.h"
#include "Map.h"

namespace structropolis
{
  class Field
  {
  private:
    Map map_;

  public:
    Field(const Map& map) : map_(map)
    {
    }

    void Draw()
    {
      for (auto& cell : map_)
      {
        cell.Draw();
      }
    }

    Field LoadFromFile(const std::string& name)
    {
      std::vector<Cell> cells_;
      uint16_t i = 0;
      uint16_t j = 0;

    }
  };
}