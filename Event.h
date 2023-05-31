#pragma once

#include "Handler.h"

namespace re::utility
{
  template<typename ...Args>
  class Event
  {
    using Handler = Handler<Args...>;

  protected:
    struct HandlerRequest
    {
      void (Event::* operation)(Handler*);
      Handler* handler;
    };

  private:
    std::set<Handler*> handlers_;
    std::vector<HandlerRequest> requests_;
    uint32_t count_ = 0;

  public:
    constexpr Event() = default;

    Event(const Event& other) = delete;

    Event(Event&& other) noexcept = delete;

    void Connect(Handler* handler)
    {
      if (count_ != 0)
      {
        requests_.emplace_back(&Event::Connect, handler);
      }
      else
      {
        handlers_.insert(handler);
      }
    }

    void Disconnect(Handler* handler)
    {
      if (count_ != 0)
      {
        requests_.emplace_back(&Event::Disconnect, handler);
      }
      else
      {
        handlers_.erase(handler);
      }
    }


    void Notify(Args... args)
    {
      ++count_;
      for (auto& handler : handlers_)
      {
        handler->Execute(args...);
      }
      --count_;

      if (count_ == 0)
      {
        for (const auto& request : requests_)
        {
          (this->*request.operation)(request.handler);
        }

        requests_.clear();
      }
    }
  };
}

