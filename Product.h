#pragma once

#include "Material.h"

namespace structropolis
{
  template<typename Instance>
  class Product : public Material<Instance>
  {
    using Base = Material<Instance>;

  protected:
    uint32_t cost_;
    uint32_t pack_size_;

  public:
    explicit Product(const uint32_t cost, const uint32_t pack_size, const uint32_t value = 0) : Base(value), cost_(cost), pack_size_(pack_size)
    {

    }

    Gold ToGold() const
    {
      return Gold(Base::value_ / pack_size_ * cost_);
    }
  };

  class Wood : public Product<Wood>
  {
  public:
    explicit Wood(const uint32_t value = 0) : Product(1, 100)
    {

    }
  };

  class Stone : public Product<Wood>
  {
  public:
    explicit Stone(const uint32_t value = 0) : Product(5, 10)
    {

    }
  };

  class Steel : public Product<Wood>
  {
  public:
    explicit Steel(const uint32_t value = 0) : Product(1, 2)
    {

    }
  };
}