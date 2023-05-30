#pragma once

#include <ranges>
#include <string>
#include <vector>

#include "ColorsDictionary.h"
#include "Pixel.h"
#include "Size2.h"
#include "Window.h"

namespace my_game::drawing {

	class Texture {
	private:
		std::vector<Pixel> data_{};
		utility::Size2 size_;

	public:
		Texture(const std::string& main_data,
			const utility::Size2& size) :
			size_(size)
		{
			using std::ranges::views::iota;

			for (auto i : iota(0u, main_data.size()))
			{
				data_.emplace_back(main_data[i]);
			}
		}

		Texture(const std::string& main_data,
			const std::string& color_data,
			const utility::Size2& size) :
			size_(size)
		{
			using std::ranges::views::iota;

			for (auto i : iota(0u, main_data.size()))
			{
				if (i < color_data.size())
				{
					data_.emplace_back(main_data[i], core::Rgb(color_data[i]));
				}
				else
				{
					data_.emplace_back(main_data[i]);
				}
			}
		}

		Texture(const std::vector<Pixel>& data, const utility::Size2& size) :
			data_(data),
			size_(size) {}

		[[nodiscard]]
		const std::vector<Pixel>& GetData() const
		{
			return data_;
		}

		[[nodiscard]]
		const utility::Size2& GetSize() const
		{
			return size_;
		}

		[[nodiscard]]
		const Pixel& GetPixel(const uint32_t i) const
		{
			return data_[i];
		}

		[[nodiscard]]
		const Pixel& GetPixel(const utility::Size2& p) const
		{
			return GetPixel(p.GetX() + p.GetY() * size_.GetWidth());
		}

		void DrawInMask(core::Window& mask) const
		{
			using std::ranges::views::iota;

			mask.SetAsOwner();
			for (auto i : iota(0u, mask.GetRect().GetSquare())) {
				ColorsDictionary& colors_dictionary = ColorsDictionary::GetInstance();
				const Pixel pixel = GetPixel(i);
				mask.FillCell(pixel.GetValue(),
					core::CursesAdapter::GetColor(*colors_dictionary.GetIndex(core::Rgb(pixel.GetColor()))));
			}

			mask.Update();
		}
	};
}
