#include "Console.h"
#include "Cursor.h"
#include "Time.h"
#include "SplashScreen.h"
#include "LoadingScreen.h"
#include "Cell.h"
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

	using namespace structropolis;

	auto& console = Console::GetInstance();
	auto& cursor = Cursor::GetInstance();
	cursor.Hide();
	auto& time = Time::GetInstance();
	time.Start();
	time.SetDeltaTime(10);
	auto splash_screen = SplashScreen();
	auto loading_screen = LoadingScreen();

	auto cell = Cell(Size2::kZero, "ForestCell", 0, 40, 0, 0);
	auto cell1 = Cell({ 5, 0 }, "StoneCell", 0, 0, 37, 2);
	auto cell2 = Cell({5, 3}, "SteelCell", 0, 0, 0, 10);

	splash_screen.GetComponent<AnimationComponent>();
	std::function on_logo_end = [&] {
		splash_screen.Hide();
		loading_screen.Show();
	};

	loading_screen.GetComponent<AnimationComponent>();
	std::function on_loading_end = [&] {
		loading_screen.Hide();
		cell.Draw();
		cell1.Draw();
		cell2.Draw();
	};

	splash_screen.OnScreenShown.Connect(on_logo_end);
	loading_screen.OnScreenShown.Connect(on_loading_end);

	splash_screen.Show();

	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	}

	return 0;
}