#pragma once

#include <cstdint>
#include <conio.h>


namespace re::input {

  enum class Keys {
    kArrow,
    kLetter,
    kDigit,
    kSpace,
    kNone
  };

  struct Key {
    Keys type;
    uint8_t code;
  };

  class Input {
  public:
    static constexpr uint8_t kAdditionalArrowsCodes[] = { 0, 224 };

    static constexpr uint8_t kUpArrowCode = 72;
    static constexpr uint8_t kRightArrowCode = 77;
    static constexpr uint8_t kDownArrowCode = 75;
    static constexpr uint8_t kLeftArrowCode = 80;

  public:
    static Key Get()
    {
      if (_kbhit()) {
        uint8_t code = _getch();
        if (code >= '0' && code <= '9')
        {
          return Key{ Keys::kDigit, code };
        }

        if (code >= ' ')
        {
          return Key{ Keys::kSpace, code };
        }

      	if (code >= 'A' && code <= 'Z' || code >= 'a' && code <= 'z')
      	{
          return Key{ Keys::kLetter, code };
      	}

        if (code == kAdditionalArrowsCodes[0] || code == kAdditionalArrowsCodes[1])
        {
          if (IsArrowKeyCode(code = _getch())) {
            return Key{ Keys::kArrow, code };
          }
        }
      }

      return Key{ Keys::kNone };
    }

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

