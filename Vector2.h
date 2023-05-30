#pragma once

#include <windows.h>
#include <cmath>

namespace re::utility
{
	template<class T> requires std::integral<T> || std::floating_point<T>
	class Vector2 {
	public:
		const static Vector2 kZero;

	private:
		T x_, y_;

	public:
		Vector2(const Vector2& other) = default;

		Vector2(Vector2&& other) noexcept = default;

		Vector2& operator=(const Vector2& other) = default;

		Vector2& operator=(Vector2&& other) noexcept = default;

		constexpr Vector2(const T x, const T y) :
			x_(x),
			y_(y) {}

		explicit operator COORD()
		{
			return { x_, y_ };
		}

		[[nodiscard]]
		constexpr T GetX() const
		{
			return x_;
		}

		[[nodiscard]]
		constexpr T GetY() const
		{
			return y_;
		}

		void SetX(T x)
		{
			x_ = x;
		}

		void SetY(T y)
		{
			y_ = y;
		}

		[[nodiscard]]
		float GetMagnitude() const
		{
			return std::sqrt(x_ * x_ + y_ * y_);
		}

		Vector2& operator+=(const Vector2& rhs)
		{
			return *this = *this + rhs;
		}

		Vector2& operator-=(const Vector2& rhs)
		{
			return *this = *this - rhs;
		}

		Vector2& operator*=(T rhs)
		{
			return *this = *this * rhs;
		}

		Vector2& operator/=(T rhs)
		{
			return *this = *this / rhs;
		}

		bool operator==(const Vector2& rhs) const
		{
			return x_ == rhs.x_ && y_ == rhs.y_;
		}

		bool operator!=(const Vector2& rhs) const
		{
			return !(rhs == *this);
		}

		Vector2 operator+(const Vector2& rhs) const {
			return {
					static_cast<T>(x_ + rhs.x_),
					static_cast<T>(y_ + rhs.y_)
			};
		}

		Vector2 operator-(const Vector2& rhs) const {
			return {
					static_cast<T>(x_ - rhs.x_),
					static_cast<T>(y_ - rhs.y_)
			};
		}

		Vector2 operator*(const T rhs) const {
			return {
					static_cast<T>(x_ * rhs),
					static_cast<T>(y_ * rhs)
			};
		}

		Vector2 operator/(const T rhs) const {
			return {
					static_cast<T>(x_ / rhs),
					static_cast<T>(y_ / rhs)
			};
		}

		friend Vector2 operator*(const T lhs, const Vector2& rhs) {
			return rhs * lhs;
		}
	};

	template<class T> requires std::integral<T> || std::floating_point<T>
	const Vector2<T> Vector2<T>::kZero{0, 0};
}