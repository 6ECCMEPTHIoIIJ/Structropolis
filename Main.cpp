#include "RealEngine.h"
#include "Field.h"
#include "LogoScreen.h"
#include "Builder.h"
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
  auto logo_screen = LogoScreen();

  auto& field = Field::GetInstance();

  std::function on_logo_end = [&]
  {
    splash_screen.Hide();
    logo_screen.Show();
  };

  Size2 p = Size2::kZero;

  auto& storage = Storage::GetInstance();
  storage.GetComponent<ResourcesComponent>()->operator+=({ 10, 0, 0, 0 });

  auto scr = Window({ 10, 0, 20, 1 });
  std::function on_key_pressed = [&](const uint8_t code)
  {
    if (code == 'b')
    {
      MiningBuilder("Sawmill", 1, 0, 0, 0, 0, 5, 0, 0, 800).Build(p);
    }
  };

  std::function on_arrow_pressed = [&](const uint8_t code)
  {
    if (code == Input::kUpArrowCode)
    {
      if (p.GetY() == 0)
      {
        p.SetY(5);
      }
      else
      {
        p -= {0, 1};
      }
    }
    else if (code == Input::kDownArrowCode)
    {
      if (p.GetY() == 5)
      {
        p.SetY(0);
      }
      else
      {
        p += {0, 1};
      }
    }
    else if (code == Input::kLeftArrowCode)
    {
      if (p.GetX() == 0)
      {
        p.SetX(12);
      }
      else
      {
        p -= {1, 0};
      }
    }
    else if (code == Input::kRightArrowCode)
    {
      if (p.GetX() == 12)
      {
        p.SetX(0);
      }
      else
      {
        p += {1, 0};
      }
    }
  };


  std::function on_back_pressed = [&]
  {
    if (scr.GetCursor().GetX() > 0)
    {
      scr.GetCursor().MoveBackward();
      scr.ClearCell();
      scr.GetCursor().MoveBackward();
      scr.Update();
    }

  };

  auto& input = Input::GetInstance();

  std::function on_game_logo_end = [&]
  {
    logo_screen.Hide();
    loading_screen.Show();
  };

  std::function on_loading_end = [&]
  {
    loading_screen.Hide();
    input.OnCommonKeyPressed.Connect(on_key_pressed);
    input.OnBackspaceKeyPressed.Connect(on_back_pressed);
    input.OnArrowKeyPressed.Connect(on_arrow_pressed);
    field.GetComponent<PositionComponent>()->SetPos({ 5, 3 });
    field.Draw();

  };

  splash_screen.OnScreenShown.Connect(on_logo_end);
  loading_screen.OnScreenShown.Connect(on_loading_end);
  logo_screen.OnScreenShown.Connect(on_game_logo_end);


  splash_screen.Show();

  while (true)
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
  }

  return 0;
}