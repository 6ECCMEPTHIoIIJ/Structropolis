#pragma once
#include <string>
#include <stdexcept>
#include <fstream>
#include <format>

namespace re::sources
{
  class Loader
  {
  protected:
    const char bound_char_;
    mutable std::string tmp_;
    mutable std::fstream file_;

  protected:
    Loader(const char bound_char) : bound_char_(bound_char)
    {
    }

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
      tmp_.clear();
    }

    bool IsBoundCharTaken() const
    {
      return file_.peek() == bound_char_;
    }

    uint16_t GetX() const
    {
      uint16_t x = 0;
      SkipChar();
      while (!IsBoundCharTaken())
      {
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
      for ([[maybe_unused]] auto i : iota(0u, length))
      {
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
      while (!IsBoundCharTaken())
      {
        data += ParseString(x);
        ++y;
      }

      SkipRow();

      return { data, {x, y} };
    }
  };
}
