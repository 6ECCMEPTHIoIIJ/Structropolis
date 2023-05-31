#pragma once

#include <algorithm>

#include "Size2.h"
#include "Signal.h"

namespace re::utility
{
  class Rectangle
  {
  public:
    Signal<void(Rectangle)> OnChanged;

  private:
    Size2 p_1_, p_2_;

  public:
    constexpr Rectangle(const Rectangle& rect) : Rectangle(rect.GetLeftTopCorner(), rect.GetRightBottomCorner())
    {
    }

    Rectangle& operator=(const Rectangle& rect)
    {
      p_1_ = rect.p_1_;
      p_2_ = rect.p_2_;
      OnChanged.Notify(*this);
      return *this;
    }

    constexpr Rectangle(const Size2& p_1, const Size2& p_2)
      : p_1_(std::min(p_1.GetX(), p_2.GetX()), std::min(p_1.GetY(), p_2.GetY())),
      p_2_(std::max(p_1.GetX(), p_2.GetX()), std::max(p_1.GetY(), p_2.GetY()))
    {

    }

    constexpr Rectangle(const uint16_t x_1,
      const uint16_t y_1,
      const uint16_t x_2,
      const uint16_t y_2)
      : p_1_(std::min(x_1, x_2), std::min(y_1, y_2)),
      p_2_(std::max(x_1, x_2), std::max(y_1, y_2))
    {
    }

    [[nodiscard]]
    Size2 GetPos() const
    {
      return p_1_;
    }

    [[nodiscard]]
    uint16_t GetTop() const
    {
      return p_1_.GetY();
    }

    [[nodiscard]]
    uint16_t GetBottom() const
    {
      return p_2_.GetY();
    }

    [[nodiscard]]
    uint16_t GetLeft() const
    {
      return p_1_.GetX();
    }

    [[nodiscard]]
    uint16_t GetRight() const
    {
      return p_2_.GetX();
    }

    [[nodiscard]]
    Size2 GetLeftTopCorner() const
    {
      return p_1_;
    }

    [[nodiscard]]
    Size2 GetRightBottomCorner() const
    {
      return p_2_;
    }

    [[nodiscard]]
    Size2 GetLeftBottomCorner() const
    {
      return { p_1_.GetX(), p_2_.GetY() };
    }

    [[nodiscard]]
    Size2 GetRightTopCorner() const
    {
      return { p_2_.GetX(), p_1_.GetY() };
    }

    [[nodiscard]]
    Size2 GetCenter() const
    {
      return (p_1_ + p_2_) / 2;
    }

    [[nodiscard]]
    Size2 GetSize() const
    {
      return p_2_ - p_1_;
    }

    [[nodiscard]]
    uint16_t GetWidth() const
    {
      return GetSize().GetX();
    }

    [[nodiscard]]
    uint16_t GetHeight() const
    {
      return GetSize().GetY();
    }

    [[nodiscard]]
    uint32_t GetSquare() const
    {
      return GetWidth() * GetHeight();
    }

    void SetPos(const Size2& p)
    {
      *this = Rectangle(p, p + GetSize());
      OnChanged.Notify(*this);
    }

    void SetLeft(const uint16_t left)
    {
      *this = Rectangle(left, p_1_.GetY(), p_2_.GetX(), p_2_.GetY());
      OnChanged.Notify(*this);
    }

    void SetTop(const uint16_t top)
    {
      *this = Rectangle(p_1_.GetX(), top, p_2_.GetX(), p_2_.GetY());
      OnChanged.Notify(*this);
    }

    void SetBottom(const uint16_t bottom)
    {
      *this = Rectangle(p_1_.GetX(), p_1_.GetY(), p_2_.GetX(), bottom);
      OnChanged.Notify(*this);
    }

    void SetRight(const uint16_t right)
    {
      *this = Rectangle(p_1_.GetX(), p_1_.GetY(), right, p_2_.GetY());
      OnChanged.Notify(*this);
    }

    void SetLeftTopCorner(const Size2& left_top)
    {
      *this = Rectangle(left_top, p_2_);
      OnChanged.Notify(*this);
    }

    void SetRightBottomCorner(const Size2& right_bottom)
    {
      *this = Rectangle(p_1_, right_bottom);
      OnChanged.Notify(*this);
    }

    void SetRightTopCorner(const Size2& right_top)
    {
      *this = Rectangle(p_1_.GetX(),
        right_top.GetY(),
        right_top.GetX(),
        p_2_.GetY());
      OnChanged.Notify(*this);
    }

    void SetLeftBottomCorner(const Size2& left_bottom)
    {
      *this = Rectangle(left_bottom.GetX(),
        p_1_.GetY(),
        p_2_.GetX(),
        left_bottom.GetY());
      OnChanged.Notify(*this);
    }

    void SetWidth(const uint16_t width)
    {
      p_2_.SetX(p_1_.GetX() + width);
      OnChanged.Notify(*this);
    }

    void SetHeight(const uint16_t height)
    {
      p_2_.SetY(p_1_.GetY() + height);
      OnChanged.Notify(*this);
    }

    void SetSize(const Size2& size)
    {
      SetWidth(size.GetX());
      SetHeight(size.GetY());
      OnChanged.Notify(*this);
    }

    void SetCenter(const Size2& p)
    {
      Size2 shift = p - GetCenter();
      p_1_ += shift;
      p_2_ += shift;
      OnChanged.Notify(*this);
    }
  };
}


