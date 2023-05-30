#pragma once

#include <vector>

#include "AnimationPoint.h"

namespace re::drawing {

  class AnimationCurve {
  public:
    using Iterator = std::vector<AnimationPoint>::iterator;
    using ConstIterator = std::vector<AnimationPoint>::const_iterator;
  private:
    std::vector<AnimationPoint> animation_points_;

  public:
    explicit AnimationCurve(std::vector<AnimationPoint> animation_points) : animation_points_(std::move(animation_points)) {}

    [[nodiscard]]
  	const std::vector<AnimationPoint>& GetAnimationPoints() const
    {
      return animation_points_;
    }

    Iterator begin()
    {
      return animation_points_.begin();
    }

    [[nodiscard]] ConstIterator begin() const
    {
      return animation_points_.begin();
    }

    Iterator end()
    {
      return animation_points_.end();
    }

    [[nodiscard]] ConstIterator end() const
    {
      return animation_points_.end();
    }

    [[nodiscard]] bool IsEmpty() const
    {
      return animation_points_.empty();
    }
  };

}

