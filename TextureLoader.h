#pragma once

#include <string>
#include <fstream>

#include "PointerList.h"
#include "Singleton.h"
#include "Size2.h"
#include "Texture.h"
#include "TextureDictionary.h"
#include <format>

namespace re::sources {

  constexpr char kTextureFolderName[] = "";
  constexpr char kTextureExt[] = ".txt";
  constexpr char kBoundChar = '+';

  enum class TextureType {
    MAIN,
    COLOR,
    NONE
  };

  class TextureLoader : public utility::Singleton<TextureLoader> {
    friend class utility::Singleton<TextureLoader>;

  private:
    mutable std::string tmp_;
    mutable std::fstream file_;

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

  private:
    void OpenFile(const std::string& name) const
    {
      file_.open(name);
      if (!file_)
      {
        throw std::runtime_error(std::format("Can`t open file \"{}\", no such file.", name));
      }
    }

    void CloseFile() const
    {
      file_.close();
    }

    bool IsFileEnd() const
    {
      return file_.eof();
    }

    TextureType GetTextureType() const
    {
      switch (file_.peek()) {
      case 'T':return TextureType::MAIN;
      case 'F':return TextureType::COLOR;
      default: return TextureType::NONE;
      }
    }

    bool IsBoundCharTaken() const
    {
      return file_.peek() == kBoundChar;
    }

    char GetChar() const
    {
      return static_cast<char>(file_.get());
    }

    void SkipChar() const
    {
      file_.ignore();
    }

    void SkipRow() const
    {
      std::getline(file_, tmp_);
    }

    uint16_t GetX() const
    {
      uint16_t x = 0;
      SkipChar();
      while (!IsBoundCharTaken()) {
        SkipChar();
        ++x;
      }

      SkipRow();

      return x;
    }

    std::string ParseString(const uint16_t length) const
    {
      using std::ranges::views::iota;

      std::string str;
      SkipChar();
      for ([[maybe_unused]] auto i : iota(0u, length)) {
        str += GetChar();
      }

      SkipRow();

      return str;
    }

    std::pair<std::string, utility::Size2> Parse() const
    {
      uint16_t x = GetX();
      uint16_t y = 0;
      std::string data;
      while (!IsBoundCharTaken()) {
        data += ParseString(x);
        ++y;
      }

      SkipRow();

      return { data, {x, y} };
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

