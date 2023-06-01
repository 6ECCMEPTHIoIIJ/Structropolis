#pragma once

#include "RealEngine.h"

namespace structropolis
{
  class LogoScreen : public Screen
  {
  public:
    LogoScreen()
      : Screen("GameLogo", AnimationCurve{ {
        {0, 100},
        {1, 30},
        {2, 20},
        {3, 15},
        {4, 10},
        {5, 5},
        {6, 5},
        {7, 7},
        {8, 10},
        {9, 15},
        {10, 20},
        {11, 25},
        {12, 50},
        {13, 30},
        {12, 200}
        }})
    {

    }
  };
}

