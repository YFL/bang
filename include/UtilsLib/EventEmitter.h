#pragma once

#include <EventHandler.h>

#include <algorithm>
#include <format>
#include <iostream>
#include <memory>
#include <vector>


namespace Utils
{

// TODO: Let's rewrite this, so that it accepts IEventHandler objects in the RegisterHandler
//  function based on HandlerArgumentType.

template<typename HandlerArgumentType>
class IEventEmitter
{
public:
  auto RegisterHandler(std::shared_ptr<IEventHandler<HandlerArgumentType>> &&handler) -> void
  {
    std::cerr << this << " Registered handler" << std::endl;
    _handlers.emplace_back(handler);
    std::cerr << std::format("Handlers size: {}", _handlers.size()) << std::endl;
  }

protected:
  auto Emit(const HandlerArgumentType &arg) -> void
  {
    std::cerr
      << std::format(
        "{:x} Handlers size before removal: {}",
        reinterpret_cast<uint64_t>(this),
        _handlers.size())
      << std::endl;

    const auto [eraseStart, eraseEnd] = std::ranges::remove_if(
      _handlers,
      [](std::weak_ptr<IEventHandler<HandlerArgumentType>>& handler)
      {
        return handler.expired();
      });
    _handlers.erase(eraseStart, eraseEnd);

    std::cerr
      << std::format(
        "{:x} Handlers size after removal: {}",
        reinterpret_cast<uint64_t>(this),
        _handlers.size())
      << std::endl;

    std::ranges::for_each(
      _handlers,
      [&arg](std::weak_ptr<IEventHandler<HandlerArgumentType>> &handler)
      {
        handler.lock()->Handle(arg);
      });
  }

protected:
  std::vector<std::weak_ptr<IEventHandler<HandlerArgumentType>>> _handlers;
};

} // namespace Utils