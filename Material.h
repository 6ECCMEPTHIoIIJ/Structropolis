#pragma once

#include <cstdint>
#include <stdexcept>

namespace structropolis
{
  template<typename Instance>
  class Material
  {
  protected:
    uint32_t value_;

  public:
    explicit Material(const uint32_t value = 0) : value_(value)
    {

    }

    virtual ~Material() = default;

    void SetValue(const uint32_t value)
    {
      value_ = value;
    }

    [[nodiscard]]
    uint32_t GetValue() const
    {
      return value_;
    }

    Instance& operator+=(const Instance& other)
    {
      value_ += other.value_;
      return *this;
    }

    Instance& operator-=(const Instance& other)
    {
      value_ -= other.value_;
      return *this;
    }

    Instance operator+(const Instance& other) const
    {
      return Instance(*this) += other;
    }

    Instance operator-(const Instance& other) const
    {
      return Instance(*this) -= other;
    }

    bool operator<(const Instance& other) const
    {
      return value_ < other.value_;
    }

    bool operator>=(const Instance& other) const
    {
      return !(*this < other);
    }

    bool operator>(const Instance& other) const
    {
      return other < *this;
    }

    bool operator<=(const Instance& other) const
    {
      return !(other < *this);
    }

    bool operator==(const Instance& other) const
    {
      return value_ == other.value_;
    }

    bool operator!=(const Instance& other) const
    {
      return !(*this == other);
    }
  };

  class Gold : public Material<Gold>
  {
    using Material::Material;
  };
}


