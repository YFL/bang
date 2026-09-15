#pragma once

#include <DrawArea.h>

#include <ECS.h>
#include <EventEmitter.h>

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
using PositionablePtrVector = std::vector<PositionablePointer>;

class Positionable
  : public Utils::IEventEmitter<std::function<void()>>
  , public Utils::Component
  , public std::enable_shared_from_this<Positionable>
{
public:
  Positionable(
    const Utils::EntityPointer &parentEntity,
    const PositionablePointer &parentPositionable,
    const Utils::DrawArea &drawArea)
    : Utils::Component {parentEntity}
    , _parent {parentPositionable}
    , _drawArea {drawArea}
  {
    std::cerr
      << std::format(
        "Positionable: {} {} {}",
        Id.str(),
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
        Id.str(),
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

  auto GetParent() const -> PositionablePointer
  { return _parent.lock(); }

  auto SwitchParent(PositionablePointer &parent) -> void;
  auto SetPosition(const Utils::Position &position) -> void;
  virtual auto AddChild(const PositionablePointer &child) -> void;
  auto RemoveChild(const xg::Guid &childId) -> void;

protected:
  PositionableWeakPtr _parent = {};
  PositionablePtrVector _children = {};
  //! Draw area's position is relative to parent
  Utils::DrawArea _drawArea = {};
};

} // namespace Graphics
