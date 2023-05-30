#pragma once
#include "AnimationCurve.h"
#include "Signal.h"
#include "Sprite.h"
#include "Time.h"

namespace my_game::drawing {

	class Animation {
	public:
		mutable utility::Signal<void()> OnAnimationEnd;

	private:
		core::Time& time_;
		Sprite sprite_;
		AnimationCurve animation_curve_;
		AnimationCurve::Iterator it_;
		std::function<void(uint64_t)> play_function_;
		std::function<void(uint64_t)> play_one_shot_function_;

		uint64_t prev_time_ = 0;
		uint64_t cur_time_ = 0;

	public:
		explicit Animation(const Sprite& sprite) :
			time_(core::Time::GetInstance()),
			sprite_(sprite),
			animation_curve_({}),
			it_(animation_curve_.begin()) {
			play_function_ = [this](const uint64_t time) { Play(time, true); };
			play_one_shot_function_ =
				[this](const uint64_t time) { Play(time, false); };
		}

		Animation(const Sprite& sprite, AnimationCurve points) :
			time_(core::Time::GetInstance()),
			sprite_(sprite),
			animation_curve_(std::move(points)),
			it_(animation_curve_.begin()) {
			play_function_ = [this](const uint64_t time) { Play(time, true); };
			play_one_shot_function_ =
				[this](const uint64_t time) { Play(time, false); };
		}

		Animation(const Animation& other) :
			time_(core::Time::GetInstance()),
			sprite_(other.sprite_),
			animation_curve_(other.animation_curve_), it_(animation_curve_.begin()) {
			play_function_ = [this](const uint64_t time) { Play(time, true); };
			play_one_shot_function_ =
				[this](const uint64_t time) { Play(time, false); };
		}

		~Animation() {
			Stop();
			sprite_.Clear();
		}

		const Sprite& GetSprite() const
		{
			return sprite_;
		}

		void PlayOneShot()
		{
			Reset();
			if (animation_curve_.IsEmpty()) {
				return;
			}

			time_.OnLogicTick.Connect(play_one_shot_function_);
		}

		void Play()
		{
			Reset();
			if (animation_curve_.IsEmpty()) {
				return;
			}

			time_.OnLogicTick.Connect(play_function_);
		}

		void Stop()
		{
			time_.OnLogicTick.Disconnect(play_function_);
			time_.OnLogicTick.Disconnect(play_one_shot_function_);
		}

	private:
		void Reset()
		{
			sprite_.ChangeCurrentImage(0);
			sprite_.Draw();

			prev_time_ = cur_time_;
			Stop();
		}

		void Play(const uint64_t time, const bool need_loop)
		{
			cur_time_ = time;

			if (cur_time_ - prev_time_ >= it_->GetDeltaTime()) {
				ToNextAnimationPoint(need_loop);
			}
		}

		void ToNextAnimationPoint(const bool need_loop)
		{
			prev_time_ = cur_time_;
			++it_;
			if (it_ == animation_curve_.end()) {
				it_ = animation_curve_.begin();

				OnAnimationEnd.Notify();

				if (!need_loop) {
					Stop();
					return;
				}
			}

			sprite_.ChangeCurrentImage(it_->GetTextureIndex());
			sprite_.Draw();
		}
	};

}
