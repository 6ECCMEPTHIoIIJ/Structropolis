#pragma once

#include <cstdint>
#include <locale>

namespace re::core
{
  class Rgb
  {
  public:
    const static Rgb kRed;
    const static Rgb kGreen;
    const static Rgb kBlue;
    const static Rgb kBlack;
    const static Rgb kWhite;
    const static Rgb kGrey;
    const static Rgb kYellow;

    constexpr static uint16_t kMinValue = 0;
    constexpr static uint16_t kMaxValue = 1000;
    constexpr static uint16_t kAverageValue = (kMaxValue + kMinValue) / 2;

  private:
    uint16_t r_;
    uint16_t g_;
    uint16_t b_;

  public:
    constexpr Rgb() : r_(kMaxValue), g_(kMaxValue), b_(kMaxValue)
    {
    }

    constexpr Rgb(const uint16_t r, const uint16_t g, const uint16_t b) : r_(r), g_(g), b_(b)
    {
    }

    constexpr explicit Rgb(const char ch) : Rgb(
      ch == 'r' || ch == 'R' ? kRed :
      ch == 'g' || ch == 'G' ? kGreen :
      ch == 'b' || ch == 'B' ? kBlue :
      ch == 'k' || ch == 'K' ? kBlack :
      ch == 'y' || ch == 'Y' ? kYellow :
      ch == 'h' || ch == 'H' ? kGrey : kWhite)
    {
    }

    [[nodiscard]]
    uint16_t GetR() const
    {
      return r_;
    }

    [[nodiscard]]
    uint16_t GetG() const
    {
      return g_;
    }

    [[nodiscard]]
    uint16_t GetB() const
    {
      return b_;
    }

    bool operator==(const Rgb& rhs) const
    {
      return r_ == rhs.r_ &&
        g_ == rhs.g_ &&
        b_ == rhs.b_;
    }

    bool operator!=(const Rgb& rhs) const
    {
      return !(rhs == *this);
    }
  };

  const Rgb Rgb::kRed{kMaxValue, kMinValue, kMinValue};
  const Rgb Rgb::kGreen{kMinValue, kMaxValue, kMinValue};
  const Rgb Rgb::kBlue{kMinValue, kMinValue, kMaxValue};
  const Rgb Rgb::kYellow{kMaxValue, kMaxValue, kMinValue};
  const Rgb Rgb::kBlack{kMinValue, kMinValue, kMinValue};
  const Rgb Rgb::kWhite{kMaxValue, kMaxValue, kMaxValue};
  const Rgb Rgb::kGrey{kAverageValue, kAverageValue, kAverageValue};
}

