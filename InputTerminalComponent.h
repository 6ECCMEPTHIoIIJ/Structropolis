#pragma once

#include "RealEngine.h"

namespace structropolis
{
  class InputTerminalComponent : public IComponent
  {
  public:
    Signal<void()> OnCommandConfirmed;

  private:
    Window command_string_;
    std::string command_;
    const uint16_t max_length_;
    uint16_t cursor_pos_ = 0;

    std::function<void(uint8_t)> add_ch_;
    std::function<void(uint8_t)> add_separator_;
    std::function<void(uint8_t)> move_cursor_;
    std::function<void()> delch_ch_;
    std::function<void()> submit_;

  public:
    InputTerminalComponent(const Size2 p, const uint16_t length) :
      command_string_({ p.GetX(), p.GetY(), p.GetX() + length + 2, p.GetY() + 3 }),
      max_length_(length)
    {

    }

    

    void Show()
    {
      command_string_.ShowBorder();
    }

  private:
    void Submit()
    {

    }

    void DeleteChar()
    {
      if (cursor_pos_ == 0)
      {
        return;
      }

      command_.erase(command_.begin() + cursor_pos_);
      command_string_.GetCursor().MoveBackward();
      command_string_.ClearCell();
      command_string_.GetCursor().MoveBackward();
      --cursor_pos_;
    }

    void AddSeparator()
    {
      if (cursor_pos_ == 0 ||
        command_[cursor_pos_ - 1] == ' ' ||
        (command_.length() > cursor_pos_ && command_[cursor_pos_] == ' '))
      {
        return;
      }

      InsertChar(' ');
    }

    void AddChar(const uint8_t ch)
    {
      if (cursor_pos_ == 0)
      {
        command_string_.SetAsOwner();
        command_string_.GetCursor().SetPos(1, 1);
      }

      InsertChar(ch);
    }

    void InsertChar(const uint8_t ch)
    {
      if (cursor_pos_ == max_length_)
      {
        return;
      }

      command_.insert(command_.begin() + cursor_pos_, ch);
      command_string_.FillCell(ch);
      ++cursor_pos_;
    }

    bool ValidateCommand()
    {

    }
  };
}

