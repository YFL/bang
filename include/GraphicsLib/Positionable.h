#pragma once

#include <DrawArea.h>

#include <EventEmitter.h>
#include <IdFul.h>

#include <format>
#include <functional>
#include <iostream>
#include <map>
#include <vector>

namespace Graphics
{

class Positionable : public Utils::IdFul, public Utils::IEventEmitter<std::function<void()>>
{
public:
  Positionable(Positionable *parent, const Utils::DrawArea &drawArea)
    : IdFul {}
    , _parent {parent}
    , _drawArea {drawArea}
  {
    if (_parent) _parent->AddChild(this);
    std::cerr
      << std::format(
        "Positionable: {} {} {}",
        Id,
        reinterpret_cast<uint64_t>(_parent),
        Utils::ToString(_drawArea))
      << std::endl;
  }

  Positionable(const Positionable &) = delete;
  Positionable(Positionable &&move) noexcept;

  virtual ~Positionable()
  {
    if (_parent) _parent->RemoveChild(this);
    std::cerr
      << std::format(
        "Positionable destructor: {} {} {}",
        Id,
        reinterpret_cast<uint64_t>(_parent),
        Utils::ToString(_drawArea))
      << std::endl;
  }

public:
  auto operator=(const Positionable &) -> Positionable & = delete;
  auto operator=(Positionable &&move) noexcept -> Positionable &;
  auto operator==(const Positionable &other) const -> bool;

public:
  auto GetDrawArea() const -> Utils::DrawArea
  { return _drawArea; }

  auto GetAbsoluteDrawArea() const -> Utils::DrawArea
  { return _parent ? _parent->GetAbsoluteDrawArea() + _drawArea : _drawArea; }

  auto GetParent() const -> Positionable *
  { return _parent; }

  auto SwitchParent(Positionable *parent) -> void;
  auto SetPosition(const Utils::Position &position) -> void;
  virtual auto AddChild(Positionable *child) -> void;
  auto RemoveChild(Positionable *child) -> void;

protected:
  Positionable *_parent = nullptr;
  std::vector<Positionable *> _children = {};
  //! Draw area's position is relative to parent
  Utils::DrawArea _drawArea = {};
};

} // namespace Graphics