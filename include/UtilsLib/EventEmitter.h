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
    _handlers.emplace_back(handler);
  }

protected:
  auto Emit(const HandlerArgumentType &arg) -> void
  {
    const auto [eraseStart, eraseEnd] = std::ranges::remove_if(
      _handlers,
      [](std::weak_ptr<IEventHandler<HandlerArgumentType>>& handler)
      {
        return handler.expired();
      });
    if (eraseStart != _handlers.end())
      std::cerr 
        << std::format("Number of handlers to be removed {}", std::distance(eraseStart, eraseEnd))
        << std::endl;

    _handlers.erase(eraseStart, eraseEnd);

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