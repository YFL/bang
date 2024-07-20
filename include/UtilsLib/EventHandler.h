#pragma once

namespace Utils
{

template <typename Event>
class IEventHandler
{
public:
  IEventHandler() = default;
  IEventHandler(const IEventHandler &) = default;
  IEventHandler(IEventHandler &&) = default;
  virtual ~IEventHandler() = default;

public:
  auto operator=(const IEventHandler &) -> IEventHandler & = default;
  auto operator=(IEventHandler &&) -> IEventHandler & = default;

public:
  virtual auto Handle(const Event& event) -> void = 0;
};

} // namespace Utils