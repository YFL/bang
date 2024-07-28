#pragma once

#include <DrawArea.h>

#include <EventEmitter.h>
#include <IdFul.h>

#include <format>
#include <functional>
#include <iostream>
#include <vector>

namespace Graphics
{

class Positionable;

using PositionablePointer = std::shared_ptr<Positionable>;
using PositionableWeakPtr = std::weak_ptr<Positionable>;
using PositionableWeakPtrVector = std::vector<PositionableWeakPtr>;

class Positionable
  : public Utils::IdFul
  , public Utils::IEventEmitter<std::function<void()>>
  , public std::enable_shared_from_this<Positionable>
{
public:
  Positionable(const PositionablePointer &parent, const Utils::DrawArea &drawArea)
    : IdFul {}
    , _parent {parent}
    , _drawArea {drawArea}
  {
    std::cerr
      << std::format(
        "Positionable: {} {} {}",
        Id,
        reinterpret_cast<uint64_t>(_parent.lock().get()),
        Utils::ToString(_drawArea))
      << std::endl;
  }

  Positionable(const Positionable &) = delete;
  Positionable(Positionable &&move) noexcept;

  virtual ~Positionable()
  {
    auto parentLocked = _parent.lock();
    // TODO: Do we have to remove this as parent from the children?
    if (parentLocked) parentLocked->RemoveChild(Id);
    std::cerr
      << std::format(
        "Positionable destructor: {} {} {}",
        Id,
        reinterpret_cast<uint64_t>(parentLocked.get()),
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
  { return !_parent.expired() ? _parent.lock()->GetAbsoluteDrawArea() + _drawArea : _drawArea; }

  auto GetParent() const -> std::shared_ptr<Positionable>
  { return _parent.lock(); }

  auto SwitchParent(PositionablePointer &parent) -> void;
  auto SetPosition(const Utils::Position &position) -> void;
  virtual auto AddChild(const PositionablePointer &child) -> void;
  auto RemoveChild(uint64_t childId) -> void;

protected:
  PositionableWeakPtr _parent = {};
  PositionableWeakPtrVector _children = {};
  //! Draw area's position is relative to parent
  Utils::DrawArea _drawArea = {};
};

} // namespace Graphics
