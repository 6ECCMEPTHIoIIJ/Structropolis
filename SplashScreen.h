#pragma once

#include "Screen.h"

namespace re::gameplay::environment {

	class SplashScreen : public Screen {
	public:
		SplashScreen() : Screen("Logo", drawing::AnimationCurve{{
			{0, 50},
			{ 1, 5 },
			{ 2, 5 },
			{ 3, 5 },
			{ 4, 5 },
			{ 5, 5 },
			{ 6, 5 },
			{ 7, 150 },
			{ 6, 5 },
			{ 5, 5 },
			{ 4, 5 },
			{ 3, 5 },
			{ 2, 5 },
			{ 1, 5 },
			{ 0, 50 },
			}}) {}
	};

}

