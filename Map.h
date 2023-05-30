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
    Map(const Size2 size, const std::vector<Cell>& data)
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

