#pragma once

#include "Animation.h"
#include "Component.h"
#include "Container.h"

namespace re::gameplay::components
{

  class AnimationComponent : public base::IComponent
  {
  private:
    sources::Container<std::string, drawing::Animation> animation_list_;
    mutable drawing::Animation* current_animation_ = nullptr;

  public:
    ~AnimationComponent() override = default;

    AnimationComponent(const std::initializer_list<std::pair<std::string, drawing::Animation>>& animation_list) :
      animation_list_(animation_list)
    {
    }

    void PlayAnimation(const std::string& name)
    {
      if (current_animation_ != nullptr)
      {
        current_animation_->Stop();
        current_animation_->GetSprite().Clear();
      }

      current_animation_ = const_cast<drawing::Animation*>(animation_list_.GetValue(name));
      current_animation_->Play();
    }

    void PlayOneShotAnimation(const std::string& name)
    {
      if (current_animation_ != nullptr)
      {
        current_animation_->Stop();
        current_animation_->GetSprite().Clear();
      }

      current_animation_ = const_cast<drawing::Animation*>(animation_list_.GetValue(name));
      current_animation_->PlayOneShot();
    }

    const sources::Container<std::string, drawing::Animation>& GetAnimationList() const
    {
      return animation_list_;
    }

    const drawing::Animation* GetCurrentAnimation() const
    {
      return current_animation_;
    }
  };

}

