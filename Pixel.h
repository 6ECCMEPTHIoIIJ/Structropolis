#pragma once

#include "Rgb.h"

namespace my_game::drawing {

  class Pixel {
  public:
    const static Pixel kEmpty;

  private:
    const char value_;
    const core::Rgb color_;

  public:

    // ReSharper disable once CppNonExplicitConvertingConstructor
    constexpr Pixel(const char value, const core::Rgb& color = core::Rgb::kWhite) : value_(value), color_(color) {}


    [[nodiscard]]
  	char GetValue() const
  	{
      return value_;
    }

    [[nodiscard]]
  	const core::Rgb& GetColor() const
    {
      return color_;
    }
  };

  const Pixel Pixel::kEmpty{' '};
}

