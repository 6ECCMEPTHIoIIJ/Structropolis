#pragma once

#include "Vector2.h"

namespace re::utility
{
	class Size2 : public Vector2<uint16_t> {
	public:
		using Base = Vector2;
		using Base::Base;

	public:
		// ReSharper disable once CppNonExplicitConvertingConstructor
		Size2(const Base& base) : Base(base) {}

		// ReSharper disable once CppNonExplicitConvertingConstructor
		Size2(Base&& base) noexcept : Base(base) {}

		[[nodiscard]]
		constexpr uint16_t GetWidth() const
		{
			return GetX();
		}

		[[nodiscard]]
		constexpr uint16_t GetHeight() const
		{
			return GetY();
		}

		void SetWidth(const uint16_t width)
		{
			SetX(width);
		}

		void SetHeight(const uint16_t width)
		{
			SetY(width);
		}

		[[nodiscard]]
		constexpr uint32_t GetSquare() const
		{
			return GetWidth() * GetHeight();
		}
	};
}


