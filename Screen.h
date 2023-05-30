#pragma once

#include "AnimationComponent.h"
#include "GameObject.h"
#include "Signal.h"
#include "TextureLoader.h"

namespace my_game::gameplay::environment {

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
	    const sources::TextureLoader& texture_loader = sources::TextureLoader::GetInstance();
      drawing::TextureDictionary& texture_dictionary = drawing::TextureDictionary::GetInstance();
      auto textures = texture_dictionary.GetTextures(texture_loader.LoadFromFile(name));
      auto &mask_size = textures.Get(0).GetSize();
	    const auto mask_position = core::Window::GetDefault().GetRect().GetCenter() - mask_size / 2;
      auto sprite = drawing::Sprite{ textures, mask_size, mask_position };

      return sprite;
    }
  };

}
