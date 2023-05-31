#pragma once

#include <set>
#include <vector>
#include <cstdint>
#include <functional>
#include <ranges>
#include <map>
#include <unordered_set>

namespace re::utility
{
  template<typename ...Args>
  class Handler
  {
    using HandlerFunction = std::function<void(Args...)>;

  private:
    void* receiver_;
    void** function_ptr_;
    HandlerFunction function_;

  public:
    constexpr Handler() = default;

    constexpr Handler(const Handler& other) = delete;

    constexpr Handler(Handler&& other) noexcept = delete;


    template<typename C, typename R, typename ...BindArgs>
    void Bind(C* receiver, R(C::* function)(Args..., BindArgs...), BindArgs... bind_args)
    {
      using Function = R(C::*)(Args..., BindArgs...);
      receiver_ = receiver;
      function_ptr_ = reinterpret_cast<void**>(&function);

      function_ = [&](Args...args)
      {
        (reinterpret_cast<C*>(receiver_)->**(reinterpret_cast<Function*>(function_ptr_)))(args..., bind_args...);
      };
    }

    template<typename R, typename ...BindArgs>
    void Bind(R(*function)(Args..., BindArgs...), BindArgs... bind_args)
    {
      function_ = [&](Args...args)
      {
        function(args..., bind_args...);
      };
    }

    template<typename R, typename ...BindArgs>
    void Bind(const std::function<R(Args..., BindArgs...)>& function, BindArgs... bind_args)
    {
      function_ = [&](Args...args)
      {
        function(args..., bind_args...);
      };
    }

    void Execute(Args...args)
    {
      function_(args...);
    }
  };
}

