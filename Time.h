#pragma once

#include <thread>

#include "Signal.h"
#include "Singleton.h"

namespace re::core
{

  class Time : public utility::Singleton<Time>
  {
    friend class utility::Singleton<Time>;

  public:
    mutable utility::Signal<void(uint64_t)> OnLogicTick;

  private:
    uint16_t delta_time_;
    bool active_ = false;

  public:
    void Start()
    {
      active_ = true;

      std::jthread([this]
        {
          while (active_)
          {
            LogicTick();
          }
        }).detach();
    }

    void Stop()
    {
      active_ = false;
    }

    [[nodiscard]] uint16_t GetDeltaTime() const
    {
      return delta_time_;
    }

    void SetDeltaTime(const uint16_t delta_time)
    {
      delta_time_ = delta_time;
    }

  protected:
    Time() : delta_time_(10)
    {
    }

    ~Time() override = default;

  private:
    void LogicTick() const
    {
      static uint64_t time;
      std::this_thread::sleep_for(std::chrono::milliseconds(delta_time_));
      OnLogicTick.Notify(++time);
    }
  };
}

