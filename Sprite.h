#pragma once

#include "PointerList.h"
#include "Texture.h"
#include "TextureLoader.h"
#include "TextureDictionary.h"

namespace re::drawing {

	class Sprite {
	private:
		sources::ConstPointerList<Texture> sprite_sheet_;
		mutable core::Window mask_;
		sources::ConstPointerList<Texture>::iterator it_;

	public:
		Sprite(const sources::ConstPointerList<Texture>& sprite_sheet,
			const utility::Size2 mask_size,
			const utility::Size2 position = utility::Size2::kZero) :
			sprite_sheet_(sprite_sheet),
			mask_({ position, position + mask_size }),
			it_(sprite_sheet_.begin()) {}

		explicit Sprite(const sources::ConstPointerList<Texture>& sprite_sheet) :
			sprite_sheet_(sprite_sheet),
			mask_({ utility::Size2::kZero, sprite_sheet.Get(0).GetSize() }),
			it_(sprite_sheet_.begin()) {}

		explicit Sprite(const Texture* texture) :
			sprite_sheet_({ texture }),
			mask_({ utility::Size2::kZero, texture->GetSize() }),
			it_(sprite_sheet_.begin()) {}

		Sprite(const Sprite& other) :
			sprite_sheet_(other.sprite_sheet_),
			mask_(other.mask_.GetRect()),
			it_(sprite_sheet_.begin()) {}

		Sprite(Sprite&& other) noexcept :
			sprite_sheet_(std::move(other.sprite_sheet_)),
			mask_(std::move(other.mask_)),
			it_(std::move(other.it_))
		{
		}

		[[nodiscard]]
		const sources::ConstPointerList<Texture>& GetSpriteSheet() const
		{
			return sprite_sheet_;
		}

		void ChangeCurrentImage(const uint32_t i)
		{
			it_ = sprite_sheet_.begin() + i;
		}

		void ToNextImage()
		{
			++it_;
			if (it_ == sprite_sheet_.end()) {
				it_ = sprite_sheet_.begin();
			}
		}

		void ToPreviousImage()
		{
			if (it_ == sprite_sheet_.begin()) {
				it_ = sprite_sheet_.end() - 1;
			}
			else {
				--it_;
			}
		}

		[[nodiscard]]
		const Texture* GetCurrentImage() const
		{
			return *it_;
		}

		[[nodiscard]]
		const core::Window& GetMask() const
		{
			return mask_;
		}

		void SetPos(const utility::Size2& pos) const
		{
			mask_.SetPos(pos);
		}

		void Draw() const
		{
			GetCurrentImage()->DrawInMask(mask_);
		}

		void Clear() const
		{
			mask_.Clear();
			mask_.Update();
		}

		void ShowOver(const core::Window& win) const
		{
			mask_.Overlay(win);
		}

		void ShowUnder(core::Window& win) const
		{
			win.Overlay(mask_);
		}

		static Sprite LoadFromFile(const std::string& filename)
		{
			const sources::TextureLoader& texture_loader = sources::TextureLoader::GetInstance();
			TextureDictionary& texture_dictionary = TextureDictionary::GetInstance();
			auto textures = texture_dictionary.GetTextures(texture_loader.LoadFromFile(filename));

			return Sprite(textures);
		}
	};

}
