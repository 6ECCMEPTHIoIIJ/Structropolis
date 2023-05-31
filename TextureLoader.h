#pragma once

#include <string>
#include <fstream>

#include "PointerList.h"
#include "Singleton.h"
#include "Size2.h"
#include "Texture.h"
#include "TextureDictionary.h"
#include "Loader.h"
#include <format>

namespace re::sources {

  constexpr char kTextureFolderName[] = "";
  constexpr char kTextureExt[] = ".txt";

  enum class TextureType {
    MAIN,
    COLOR,
    NONE
  };

  class TextureLoader : public utility::Singleton<TextureLoader>, public Loader {
    friend class utility::Singleton<TextureLoader>;

  public:
    ConstPointerList<std::string> LoadFromFile(const std::string& filename) const
    {
	    const std::string full_filename = kTextureFolderName + filename + kTextureExt;

      OpenFile(full_filename);
      drawing::TextureDictionary& texture_dictionary = drawing::TextureDictionary::GetInstance();
      ConstPointerList<std::string> texture_names;

      uint16_t texture_counter = 0;
	    while (!IsFileEnd()) {
        drawing::Texture t = ParseTexture();
        std::string texture_name = full_filename + std::to_string(texture_counter++);
        texture_dictionary.Add(texture_name, t);
        texture_names.push_back(texture_dictionary.GetKey(texture_name));
      }

      CloseFile();

      return texture_names;
    }

  protected:
    TextureLoader() : Loader('+')
    {
    }

    ~TextureLoader() override = default;

  private:
    TextureType GetTextureType() const
    {
      switch (file_.peek()) {
      case 'T':return TextureType::MAIN;
      case 'F':return TextureType::COLOR;
      default: return TextureType::NONE;
      }
    }

    drawing::Texture ParseTexture() const
    {
      std::pair<std::string, utility::Size2>
        main_texture{"", utility::Size2::kZero};
      std::string color_texture;
      if (GetTextureType() == TextureType::MAIN) {
        main_texture = Parse();
      }

      if (GetTextureType() == TextureType::COLOR) {
        color_texture = Parse().first;
      }

      return { main_texture.first, color_texture, main_texture.second };
    }
  };
}

