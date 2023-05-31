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
        {1, 50},
        {2, 40},
        {3, 20},
        {4, 10},
        {5, 5},
        {6, 5},
        {7, 15},
        {8, 25},
        {9, 35},
        {10, 45},
        {11, 50},
        {12, 70},
        {13, 30},
        {12, 200}
        }})
    {

    }
  };
}

