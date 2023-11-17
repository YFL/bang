#pragma once

#include <DrawArea.h>

#include <algorithm>
#include <map>
#include <vector>

namespace Graphics
{

class Positionable
{
public:
  Positionable(Positionable *parent, const DrawArea &drawArea)
    : _parent {parent}
    , _drawArea {drawArea}
  { if(parent) parent->AddChild(this); }

  Positionable(const Positionable &) = delete;
  Positionable(Positionable &&move);

  virtual ~Positionable()
  { if(_parent) _parent->RemoveChild(this); }

public:
  auto operator=(const Positionable &) -> Positionable & = delete;
  auto operator=(Positionable &&move) -> Positionable &;

public:
  auto GetDrawArea() const -> DrawArea
  { return _drawArea; }

  auto GetAbsoluteDrawArea() const -> DrawArea
  { return _parent->GetAbsoluteDrawArea() + _drawArea; }

  auto GetChildren() const -> const PositionableMap &
  { return _children; }

  auto GetParent() const -> Positionable *
  { return _parent; }

  auto GetChildCount() const -> uint32_t
  { return _childCount; }

  auto SetParent(Positionable *parent) -> void;

  auto SetPosition(const Position &position) -> void
  { _drawArea.position = position; }

  virtual auto AddChild(Positionable *child) -> void;

  auto RemoveChild(Positionable const *child) -> void;

protected:
  auto ChildAdded(Positionable *child) -> void {}

protected:
  Positionable *_parent = nullptr;
  //! Draw area's position is relative to parent
  DrawArea _drawArea = {};
  PositionableMap _children = {};
  uint32_t _childCount = 0u;
};

using PositionableMap =
  std::map<int32_t, std::map<int32_t, std::vector<Positionable *>>>;

} // namespace Graphics