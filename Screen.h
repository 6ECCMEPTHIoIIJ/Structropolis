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
          {"_", drawing::Animation{LoadSprite(sprite_name), points}},
      });

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

  private:
    static  drawing::Sprite LoadSprite(const std::string& name)
    {
      auto sprite = drawing::Sprite::LoadFromFile(name);
      const auto mask_position = core::Window::GetDefault().GetRect().GetCenter() - sprite.GetMask().GetRect().GetSize() / 2;
      sprite.SetPos(mask_position);

      return sprite;
    }
  };

}
