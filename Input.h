#pragma once

#include <cstdint>
#include <conio.h>

#include "Signal.h"
#include "Singleton.h"


namespace re::input {

  enum class KeyType
  {
    kArrow,
    kLetter,
    kDigit,
    kSpace,
    kNone
  };

  struct Key {
    KeyType type;
    uint8_t code;
  };

  class Input : public utility::Singleton<Input> {
    friend class utility::Singleton<Input>;

  public:
    static constexpr uint8_t kAdditionalArrowsCodes[] = { 0, 224 };

    static constexpr uint8_t kUpArrowCode = 72;
    static constexpr uint8_t kRightArrowCode = 77;
    static constexpr uint8_t kDownArrowCode = 75;
    static constexpr uint8_t kLeftArrowCode = 80;

    utility::Signal<void(uint8_t)> OnArrowKeyPressed;
    utility::Signal<void(uint8_t)> OnLetterKeyPressed;
    utility::Signal<void(uint8_t)> OnDigitKeyPressed;
    utility::Signal<void(uint8_t)> OnSpaceKeyPressed;

  public:


    static Key Get()
    {
      if (_kbhit()) {
        uint8_t code = _getch();
        if (code >= '0' && code <= '9')
        {
          return Key{ KeyType::kDigit, code };
        }

        if (code >= ' ')
        {
          return Key{ KeyType::kSpace, code };
        }

      	if (code >= 'A' && code <= 'Z' || code >= 'a' && code <= 'z')
      	{
          return Key{ KeyType::kLetter, code };
      	}

        if (code == kAdditionalArrowsCodes[0] || code == kAdditionalArrowsCodes[1])
        {
          if (IsArrowKeyCode(code = _getch())) {
            return Key{ KeyType::kArrow, code };
          }
        }
      }

      return Key{ KeyType::kNone };
    }


  protected:
    Input() = default;

    ~Input() = default;

  private:
    static bool IsArrowKeyCode(const uint8_t key_code)
    {
      return key_code == kUpArrowCode ||
        key_code == kDownArrowCode ||
        key_code == kLeftArrowCode ||
        key_code == kRightArrowCode;
    }
  };
}

