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
    Screen(const std::string& sprite_name, const drawing::AnimationCurve& points)
    {

      animator_ =
        AddComponent<components::AnimationComponent>(std::initializer_list<std::pair<std::string, drawing::Animation>>{
          {"_", drawing::Animation{drawing::Sprite::LoadFromFile(sprite_name), points}},
      });

      animator_->GetAnimationList().GetValue("_")->GetSprite().GetMask().GetRect().SetCenter(core::Window::GetDefault().GetRect().GetCenter());

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
      if (animator_->GetCurrentAnimation() == nullptr)
      {
        return;
      }

      animator_->GetCurrentAnimation()->GetSprite().Clear();
    }
  };

}
