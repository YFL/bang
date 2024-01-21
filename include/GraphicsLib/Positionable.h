#pragma once

#include <DrawArea.h>
#include <IdFul.h>

#include <algorithm>
#include <map>
#include <vector>

namespace Graphics
{

class Positionable : public Utils::IdFul
{
public:
  Positionable(Positionable *parent, const DrawArea &drawArea)
    : IdFul {}
    , _parent {parent}
    , _drawArea {drawArea}
  { if (parent) parent->AddChild(this); }

  Positionable(const Positionable &) = delete;
  Positionable(Positionable &&move);

  virtual ~Positionable()
  { if (_parent) _parent->RemoveChild(this); }

public:
  auto operator=(const Positionable &) -> Positionable & = delete;
  auto operator=(Positionable &&move) -> Positionable &;
  auto operator==(const Positionable &other) const -> bool;

public:
  auto GetDrawArea() const -> DrawArea
  { return _drawArea; }

  auto GetAbsoluteDrawArea() const -> DrawArea
  { return _parent ? _parent->GetAbsoluteDrawArea() + _drawArea : _drawArea; }

  auto GetParent() const -> Positionable *
  { return _parent; }

  auto SetParent(Positionable *parent) -> void;
  auto SetPosition(const Position &position) -> void;
  virtual auto AddChild(Positionable *child) -> void;
  auto RemoveChild(Positionable *child) -> void;

protected:
  // TODO: Instead of this bullshit have a proper ECS (EntityComponentSystem. Luv ya :* )
  virtual auto AddChildTo(Positionable *child, Positionable *parent) -> void
  { if (_parent) _parent->AddChildTo(child, parent); }

  virtual auto RemoveChildFrom(Positionable *child, Positionable *parent) -> void
  { if (_parent) _parent->RemoveChildFrom(child, parent); }
  
  virtual auto SetPositionOf(
    Positionable *child,
    const Position &oldPosition,
    const Position &newPosition)
    -> void
  { if (_parent) _parent->SetPositionOf(child, oldPosition, newPosition); }

protected:
  Positionable *_parent = nullptr;
  //! Draw area's position is relative to parent
  DrawArea _drawArea = {};
};

} // namespace Graphics