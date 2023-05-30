#pragma once

#include "Container.h"
#include "CursesAdapter.h"
#include "Rgb.h"
#include "RgbHasher.h"

namespace my_game::drawing {

	class ColorsDictionary :
		private sources::Container<core::Rgb, uint32_t, RgbHasher>,
		public utility::Singleton<ColorsDictionary> {
		friend class utility::Singleton<ColorsDictionary>;

	public:
		using Base = Container;

	private:
		uint16_t n_color_ = 1;

	public:
		bool Add(const core::Rgb& value)
		{
			if (n_color_ > core::CursesAdapter::GetNColorPairs() ||
				!Base::Add(value, n_color_)) {
				return false;
			}

			core::CursesAdapter::AddNewColor(n_color_, value);
			n_color_++;

			return true;
		}

		const uint32_t* GetIndex(const core::Rgb& value) const
		{
			const auto ptr = GetValue(value);
			if (ptr == nullptr) {
				return nullptr;
			}

			return ptr;
		}

		bool Has(const core::Rgb& value)
		{
			return Base::Has(value);
		}

	protected:
		ColorsDictionary()
		{
			Add(core::Rgb::kWhite);
			Add(core::Rgb::kBlack);
			Add(core::Rgb::kRed);
			Add(core::Rgb::kGreen);
			Add(core::Rgb::kBlue);
			Add(core::Rgb::kGrey);
		}

		~ColorsDictionary() override = default;
	};

}

