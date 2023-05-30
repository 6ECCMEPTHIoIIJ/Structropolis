#pragma once
#include "Container.h"
#include "PointerList.h"
#include "Texture.h"

namespace my_game::drawing {

  class TextureDictionary
    : public sources::Container<std::string, Texture>,
    public utility::Singleton<TextureDictionary> {
    friend class utility::Singleton<TextureDictionary>;
  public:
    sources::ConstPointerList<Texture> GetTextures(const sources::ConstPointerList<std::string>& names)
    {
      sources::ConstPointerList<Texture> textures;
      for (const auto& name : names) {
        auto t = GetValue(*name);
        if (t != nullptr) {
          textures.push_back(t);
        }
      }

      return textures;
    }

  protected:
    TextureDictionary() = default;

    ~TextureDictionary() override = default;
  };

}
