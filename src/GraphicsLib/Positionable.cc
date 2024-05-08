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
  _children.push_back(child);
}

auto Positionable::RemoveChild(Positionable *child) -> void
{
  const auto &it = std::remove_if(_children.begin(), _children.end(), [child](Positionable *item)
  {
    return child->id == item->id;
  });

  if(it != _children.end())
    _children.erase(it, _children.end());
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
  _drawArea.position = position;
}

} // namespace Graphics