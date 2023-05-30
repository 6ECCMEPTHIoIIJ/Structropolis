#pragma once

#include "Screen.h"

namespace re::gameplay::environment
{

  class LoadingScreen : public Screen
  {
  public:
    LoadingScreen() : Screen("Loading", drawing::AnimationCurve{{
      {0, 100},
      { 1, 15 },
      { 2, 15 },
      { 3, 15 },
      { 4, 15 },
      { 5, 15 },
      { 6, 15 },
      { 7, 15 },
      { 8, 100 },
      }})
    {
    }
  };

}

