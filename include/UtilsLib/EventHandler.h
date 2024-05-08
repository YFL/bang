#pragma once

#include <algorithm>
#include <unordered_map>
#include <vector>

#include <cstdint>

namespace Bang
{

template <typename HandlerType>
class IEventHandler
{
protected:
  auto RegisterHandler(HandlerType handler) -> void
  { _handlers.push_back(handler); }

  template<typename ...ArgsT>
  auto HandleEvent(const ArgsT ...args)
  {
    std::for_each(
      _handlers.begin(),
      _handlers.end(),
      [...args = args](const HandlerType &handler)
      {
        handler(args...);
      });
  }

protected:
  std::vector<HandlerType> _handlers;
};

} // namespace Bang