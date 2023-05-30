#pragma once

#include "CursesAdapter.h"
#include "ICursorOwner.h"
#include "Singleton.h"
#include "Size2.h"

namespace my_game::core {
	class Cursor
    : public utility::Singleton<Cursor> {
    friend class utility::Singleton<Cursor>;
  private:
    ICursorOwner* owner_ = nullptr;
    WINDOW* window_ = nullptr;

  public:
    void Hide() const
    {
      CursesAdapter::HideCursor();
    }

    void SetOwner(ICursorOwner& owner)
    {
      if (owner_ != nullptr) {
        owner_->RemoveOwnership();
      }

      owner_ = &owner;
      window_ = owner.GetWindow();
      ResetPos();
    }

    void SetPos(const utility::Size2& p)
    {
      CursesAdapter::SetCursorPosition(window_, p);
    }

    void SetPos(uint16_t x, uint16_t y)
    {
      SetPos({ x, y });
    }


    void ResetPos()
    {
      SetPos(utility::Size2::kZero);
    }

    [[nodiscard]]
		utility::Size2 GetPos() const
    {
      return CursesAdapter::GetCursorPosition(window_);
    }

    [[nodiscard]]
		uint16_t GetX() const
    {
      return GetPos().GetX();
    }

    [[nodiscard]]
		uint16_t GetY() const
    {
      return GetPos().GetY();
    }

    void MoveUp(const uint16_t n = 1)
    {
      const uint16_t win_height = CursesAdapter::GetWindowSize(window_).GetY();
      SetPos(GetX() + (GetY() - n) / win_height,
        (GetY() - n) % win_height);
    }

    void MoveDown(const uint16_t n = 1)
    {
      const uint16_t win_height = CursesAdapter::GetWindowSize(window_).GetY();
      SetPos(GetX() + (GetY() + n) / win_height,
        (GetY() + n) % win_height);
    }

    void MoveForward(const uint16_t n = 1)
    {
      const uint16_t win_width = CursesAdapter::GetWindowSize(window_).GetX();
      SetPos((GetX() + n) % win_width,
        GetY() + (GetX() + n) / win_width);
    }

    void MoveBackward(const uint16_t n = 1)
    {
      const uint16_t win_width = CursesAdapter::GetWindowSize(window_).GetX();
      SetPos((GetX() - n) % win_width,
        GetY() + (GetX() - n) / win_width);
    }

  protected:
    Cursor() = default;

    ~Cursor() override = default;
  };
}
