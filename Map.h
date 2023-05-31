#pragma once
#include "RealEngine.h"
#include "Cell.h"

namespace structropolis
{
  class Map
  {
    using Iterator = std::vector<Cell>::iterator;
    using ConstIterator = std::vector<Cell>::const_iterator;

  private:
    Size2 size_;
    std::vector<Cell> data_;

  public:
    Map(const std::string& data, const Size2 size)
      : size_(size)
    {
      using std::ranges::views::iota;

      for (auto i : iota(0u, data.length()))
      {
        data_.emplace_back(Size2{
            static_cast<uint16_t>(CellBase::kSize.GetWidth() * (i % size_.GetWidth())),
            static_cast<uint16_t>(CellBase::kSize.GetHeight() * (i / size_.GetWidth()))
          }, data[i]);
      }
    }

    Map(const std::vector<Cell>& data, const Size2 size)
      : size_(size), data_(data)
    {
    }

    [[nodiscard]]
    Size2 GetSize() const
    {
      return size_;
    }

    [[nodiscard]]
    const std::vector<Cell>& GetData() const
    {
      return data_;
    }

    Iterator begin()
    {
      return data_.begin();
    }

    Iterator end()
    {
      return data_.end();
    }

    ConstIterator begin() const
    {
      return data_.begin();
    }

    ConstIterator end() const
    {
      return data_.end();
    }
  };
}

