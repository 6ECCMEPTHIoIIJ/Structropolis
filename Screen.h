#pragma once

#include "AnimationComponent.h"
#include "GameObject.h"
#include "Signal.h"
#include "TextureLoader.h"

namespace re::gameplay::environment {

  class Screen : public base::GameObject {
  public:
    utility::Signal<void()> OnScreenShown;

  private:
    components::AnimationComponent* animator_;
    std::function<void()> on_animation_end_function_;

  public:
    explicit Screen(const std::string& sprite_name, const drawing::AnimationCurve& points)
    {

      animator_ =
        AddComponent<components::AnimationComponent>(std::initializer_list<std::pair<std::string, drawing::Animation>>{
          {"_", drawing::Animation{drawing::Sprite::LoadFromFile(sprite_name), points}},
      });

      auto& sprite = animator_->GetAnimationList().GetValue("_")->GetSprite();
      utility::Rectangle mask_rect = sprite.GetMask().GetRect();
      mask_rect.SetCenter(core::Window::GetDefault().GetRect().GetCenter());
      sprite.SetPos(mask_rect.GetPos());

      on_animation_end_function_ = [this] { OnScreenShown.Notify(); };

      animator_->GetAnimationList().GetValue("_")->OnAnimationEnd.Connect(on_animation_end_function_);
    }

    ~Screen() override
    {
      animator_->GetAnimationList().GetValue("_")->OnAnimationEnd.Disconnect(on_animation_end_function_);
    }

    void Show()
    {
      animator_->PlayOneShotAnimation("_");
    }

    void Hide()
    {
      animator_->GetCurrentAnimation()->GetSprite().Clear();
    }
  };

}
