#pragma once

#include "RealEngine.h"
#include "Map.h"

namespace structropolis
{
  constexpr char kMapFolderName[] = "";
  constexpr char kMapExt[] = ".map";

  class MapLoader : public Singleton<MapLoader>, public Loader
  {
    friend class Singleton<MapLoader>;

  public: 
    Map LoadFormFile(const std::string& filename) const
    {
      const std::string full_filename = kMapFolderName + filename + kMapExt;

      OpenFile(full_filename);

      Map map = ParseTexture();

      CloseFile();

      return map;
    }

  protected:
    MapLoader() : Loader('+')
    {
    }

    ~MapLoader() override = default;

  private:
    Map ParseTexture() const
    {
      std::pair<std::string, utility::Size2> map{"", utility::Size2::kZero};

      if (IsBoundCharTaken())
      {
        map = Parse();
      }

      return {map.first, map.second};
    }
  };
}
