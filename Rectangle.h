#pragma once

#include <algorithm>

#include "Size2.h"

namespace my_game::utility
{
	class Rectangle
	{
	private:
		Size2 p_1_, p_2_;

	public:
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
			p_2_(std::max(x_1, x_2), std::max(y_1, y_2)) {}

		[[nodiscard]]
		Size2 GetPos() const {
			return p_1_;
		}

		[[nodiscard]]
		uint16_t GetTop() const {
			return p_1_.GetY();
		}

		[[nodiscard]]
		uint16_t GetBottom() const {
			return p_2_.GetY();
		}

		[[nodiscard]]
		uint16_t GetLeft() const {
			return p_1_.GetX();
		}

		[[nodiscard]]
		uint16_t GetRight() const {
			return p_2_.GetX();
		}

		[[nodiscard]]
		Size2 GetLeftTopCorner() const {
			return p_1_;
		}

		[[nodiscard]]
		Size2 GetRightBottomCorner() const {
			return p_2_;
		}

		[[nodiscard]]
		Size2 GetLeftBottomCorner() const {
			return { p_1_.GetX(), p_2_.GetY() };
		}

		[[nodiscard]]
		Size2 GetRightTopCorner() const {
			return { p_2_.GetX(), p_1_.GetY() };
		}

		[[nodiscard]]
		Size2 GetCenter() const {
			return (p_1_ + p_2_) / 2;
		}

		[[nodiscard]]
		Size2 GetSize() const {
			return p_2_ - p_1_;
		}

		[[nodiscard]]
		uint16_t GetWidth() const {
			return GetSize().GetX();
		}

		[[nodiscard]]
		uint16_t GetHeight() const {
			return GetSize().GetY();
		}

		[[nodiscard]]
		uint32_t GetSquare() const {
			return GetWidth() * GetHeight();
		}
	};
}


