#pragma once

#include <set>
#include <vector>
#include <cstdint>
#include <functional>

namespace re::utility {

  template<class Observer> requires std::is_function_v<Observer>
  class Signal {
    using ObserverFunction = std::function<Observer>;
  protected:
    struct ObserverRequest {
      void (Signal::* operation)(const ObserverFunction&);

      const ObserverFunction& observer;
    };

  private:
    std::set<const ObserverFunction*> observers_;
    uint32_t count_ = 0;
    std::vector<ObserverRequest> requests_;

  public:
    constexpr Signal() = default;

    constexpr Signal(const Signal& other) : Signal()
    {
    }

    constexpr Signal(Signal&& other) : Signal()
    {
    }

    virtual ~Signal() = default;

    void Connect(const ObserverFunction& observer)
    {
      if (count_ != 0) {
        requests_.push_back(ObserverRequest{ &Signal::Connect, observer });
      }
      else {
        observers_.insert(&observer);
      }
    }

    void Disconnect(const ObserverFunction& observer)
    {
      if (count_ != 0) {
        requests_.push_back(ObserverRequest{ &Signal::Disconnect, observer });
      }
      else {
        observers_.erase(&observer);
      }
    }

    template<class... Args>
    void Notify(Args... args)
    {
      ++count_;
      for (const auto& observer : observers_) {
        (*observer)(args...);
      }
      --count_;

      if (count_ == 0) {
        for (const auto& request : requests_) {
          (this->*request.operation)(request.observer);
        }

        requests_.clear();
      }
    }
  };
}

