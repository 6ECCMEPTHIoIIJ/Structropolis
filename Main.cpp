#include "Console.h"
#include "Cursor.h"
#include "Time.h"
#include "SplashScreen.h"
#include "LoadingScreen.h"
#include <iostream>

int main()
{
	using namespace re::core;
	using namespace re::utility;
	using namespace re::drawing;
	using namespace re::sources;
	using namespace re::gameplay::base;
	using namespace re::gameplay::components;
	using namespace re::gameplay::environment;

	auto& console = Console::GetInstance();
	auto& cursor = Cursor::GetInstance();
	cursor.Hide();
	auto& time = Time::GetInstance();
	time.Start();
	auto splash_screen = SplashScreen();
	auto loading_screen = LoadingScreen();

	splash_screen.GetComponent<AnimationComponent>();
	std::function on_logo_end = [&] {
		splash_screen.Hide();
		loading_screen.Show();
	};

	loading_screen.GetComponent<AnimationComponent>();
	std::function on_loading_end = [&] {
		loading_screen.Hide();
	};

	splash_screen.OnScreenShown.Connect(on_logo_end);
	loading_screen.OnScreenShown.Connect(on_loading_end);

	splash_screen.Show();

	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	}

	return 0;
}