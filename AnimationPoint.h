#pragma once

#include <cstdint>

namespace re::drawing {

	class AnimationPoint {
	private:
		const uint32_t texture_index_;
		const uint32_t delta_time_;

	public:
		AnimationPoint(const uint32_t texture_index, const uint32_t delta_time) :
			texture_index_(texture_index),
			delta_time_(delta_time) {}

		[[nodiscard]]
		uint32_t GetTextureIndex() const
		{
			return texture_index_;
		}

		[[nodiscard]]
		uint32_t GetDeltaTime() const
		{
			return delta_time_;
		}
	};

}

