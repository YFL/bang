#include <Positionable.h>

#include <Exception.h>

#include <cassert>

namespace Graphics
{

Positionable::Positionable(Positionable &&move)
{
  *this = std::move(move);
}

auto Positionable::operator=(Positionable &&move) -> Positionable &
{
  move._parent->RemoveChild(&move);
  _parent = std::move(move._parent);
  move._parent = nullptr;
  _drawArea = std::move(move._drawArea);
  _parent->AddChild(this);

  return *this;
}

auto Positionable::operator==(const Positionable &other) const -> bool
{
  return id == other.id
    && GetAbsoluteDrawArea() == other.GetAbsoluteDrawArea();
}

auto Positionable::AddChild(Positionable *child) -> void
{
  if(_parent)
    _parent->AddChildTo(child, this);
}

auto Positionable::RemoveChild(Positionable *child) -> void
{
  if(_parent)
    _parent->RemoveChildFrom(child, this);
}

auto Positionable::SetParent(Positionable *parent) -> void
{
  if(_parent == parent)
    return;

  if(_parent)
    _parent->RemoveChild(this);

  _parent = parent;
  _parent->AddChild(this);
}

auto Positionable::SetPosition(const Position &position) -> void
{
  const auto oldPosition = GetAbsoluteDrawArea().position;
  _drawArea.position = position;
  if(_parent)
    _parent->SetPositionOf(this, oldPosition, GetAbsoluteDrawArea().position);
}

} // namespace Graphics