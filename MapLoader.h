#pragma once

#include "RealEngine.h"
#include "Map.h"

namespace structropolis
{
  constexpr char kMapFolderName[] = "";
  constexpr char kMapExt[] = ".map";
  constexpr char kBoundChar = '\n';

  class MapLoader : public Singleton<MapLoader>, public Loader
  {
  public: 
    Map LoadFormFile(const std::string& filename) const
    {

    }
  };
}
