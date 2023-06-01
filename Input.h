#pragma once

#include <cstdint>
#include <conio.h>

#include "Signal.h"
#include "Singleton.h"
#include <thread>

namespace re::input
{
  class Input : public utility::Singleton<Input>
  {
    friend class utility::Singleton<Input>;

  public:
    static constexpr uint8_t kLeftArrowCode = 75;
    static constexpr uint8_t kRightArrowCode = 77;
    static constexpr uint8_t kUpArrowCode = 72;
    static constexpr uint8_t kDownArrowCode = 80;

    utility::Signal<void(uint8_t)> OnArrowKeyPressed;
    utility::Signal<void(uint8_t)> OnCommonKeyPressed;
    utility::Signal<void(uint8_t)> OnSpaceKeyPressed;
    utility::Signal<void()> OnBackspaceKeyPressed;
    utility::Signal<void()> OnEnterKeyPressed;

  private:
    static constexpr uint8_t kAdditionalArrowsCodes[2] = { 0, 224 };

  protected:
    Input()
    {
      std::jthread([this]
        {
          while (true)
          {
            if (_kbhit())
            {
              uint8_t code = _getch();
              if (code >= '0' && code <= '9' || code >= 'A' && code <= 'Z' || code >= 'a' && code <= 'z')
              {
                OnCommonKeyPressed.Notify(code);
              }
              else if (code == ' ' || code == '\t')
              {
                OnSpaceKeyPressed.Notify(code);
              }
              else if (code == '\b')
              {
                OnBackspaceKeyPressed.Notify();
              }
              else if (code == '\n')
              {
                OnEnterKeyPressed.Notify();
              }
              else if (code == kAdditionalArrowsCodes[0] || code == kAdditionalArrowsCodes[1])
              {
                if (IsArrowKeyCode(code = _getch()))
                {
                  OnArrowKeyPressed.Notify(code);
                }
              }
            }
          }
        }).detach();
    }

    ~Input() = default;

  private:
    bool IsArrowKeyCode(const uint8_t key_code) const
    {
      return key_code == kUpArrowCode ||
        key_code == kDownArrowCode ||
        key_code == kLeftArrowCode ||
        key_code == kRightArrowCode;
    }
  };
}

