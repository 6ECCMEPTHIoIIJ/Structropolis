#pragma once

#include <cstdint>
#include <locale>

namespace my_game::core
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

		constexpr static uint16_t kMinValue = 0;
		constexpr static uint16_t kMaxValue = 1000;
		constexpr static uint16_t kAverageValue = (kMaxValue + kMinValue) / 2;

	private:
		uint16_t r_;
		uint16_t g_;
		uint16_t b_;

	public:
		constexpr Rgb() : r_(kMaxValue), g_(kMaxValue), b_(kMaxValue) {}

		constexpr Rgb(const uint16_t r, const uint16_t g, const uint16_t b) : r_(r), g_(g), b_(b) {}

		explicit Rgb(const char ch) {
			switch (std::tolower(ch)) {
			case 'r':
				r_ = kMaxValue;
				g_ = kMinValue;
				b_ = kMinValue;
				break;
			case 'g':
				r_ = kMinValue;
				g_ = kMaxValue;
				b_ = kMinValue;
				break;
			case 'b':
				r_ = kMinValue;
				g_ = kMinValue;
				b_ = kMaxValue;
				break;
			case 'k':
				r_ = kMinValue;
				g_ = kMinValue;
				b_ = kMinValue;
				break;
			case 'h':
				r_ = kAverageValue;
				g_ = kAverageValue;
				b_ = kAverageValue;
				break;
			default:
				r_ = kMaxValue;
				g_ = kMaxValue;
				b_ = kMaxValue;
				break;
			}
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
	const Rgb Rgb::kBlack{kMinValue, kMinValue, kMinValue};
	const Rgb Rgb::kWhite{kMaxValue, kMaxValue, kMaxValue};
	const Rgb Rgb::kGrey{kAverageValue, kAverageValue, kAverageValue};
}

