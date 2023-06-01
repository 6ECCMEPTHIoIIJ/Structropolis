#pragma once

#include <set>
#include <vector>
#include <cstdint>
#include <functional>
#include <mutex>

namespace re::utility
{

  //template<typename R, typename ...Args>
  //class Signal
  //{
  //  using Function = R(Args..);

  //protected:
  //  struct ObserverRequest
  //  {
  //    void (Signal::* operation)(Function);
  //    Function observer;
  //  };

  //private:
  //  std::set<Function> observers_;
  //  uint16_t count_ = 0;
  //  std::vector<ObserverRequest> requests_;

  //public:
  //  constexpr Signal() = default;

  //  Signal(const Signal& other) = delete;

  //  Signal(Signal&& other) = delete;

  //  virtual ~Signal() = default;

  //  template<typename C>
  //  void Connect(C* sender, R(C::*)(Args...) observer)
  //  {
  //    if (count_ != 0)
  //    {
  //      requests_.push_back(ObserverRequest{ &Signal::Connect, std::bind(&C::observer, sender)});
  //    }
  //    else
  //    {
  //      observers_.insert(&observer);
  //    }
  //  }
  //};

  template<typename ...Args>
  class Event
  {
    using ObserverFunction = void(void*, void*, Args...);

  protected:
    struct Sender
    {
      void* self;
      void* function;
    };

    struct ObserverRequest
    {
      void (Event::* operation)(ObserverFunction);
      ObserverFunction observer_function;
      Sender sender;
    };

  private:
    
    std::unordered_map<Sender, ObserverFunction> observers_;
    uint32_t count_ = 0;
    std::vector<ObserverRequest> requests_;

  public:
    template<typename C, typename R>
    void Connect(C* sender, R(C::* function)(Args...))
    {
      auto observer = [](void* sender, void* function, Args...args)
      {
        auto s = static_cast<C*>(sender);
        auto f = static_cast<R(C::*)(Args...)>(function);
        s->f(args...);
      };

      if (count_ != 0)
      {
        requests_.push_back(ObserverRequest{
          &Event::Connect,
          observer,
          Sender{sender, function} });
      }
      else
      {
        observers_.insert({ Sender{sender, function}, observer });
      }
    }
  };

  template<class Observer> requires std::is_function_v<Observer>
  class Signal
  {
    using ObserverFunction = std::function<Observer>;
  protected:
    struct ObserverRequest
    {
      void (Signal::* operation)(const ObserverFunction&);

      const ObserverFunction& observer;
    };

  private:
    std::mutex mutex_;
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
      std::lock_guard<std::mutex> lock(mutex_);
      if (count_ != 0)
      { 
        requests_.push_back(ObserverRequest{ &Signal::Connect, observer });
      }
      else
      {
        observers_.insert(&observer);
      }
    }

    void Disconnect(const ObserverFunction& observer)
    {
      std::lock_guard<std::mutex> lock(mutex_);
      if (count_ != 0)
      {
        requests_.push_back(ObserverRequest{ &Signal::Disconnect, observer });
      }
      else
      {
        observers_.erase(&observer);
      }
    }

    template<class... Args>
    void Notify(Args... args)
    {
      ++count_;
      for (const auto& observer : observers_)
      {
        (*observer)(args...);
      }
      --count_;

      if (count_ == 0)
      {
        for (const auto& request : requests_)
        {
          (this->*request.operation)(request.observer);
        }

        requests_.clear();
      }
    }
  };
}

