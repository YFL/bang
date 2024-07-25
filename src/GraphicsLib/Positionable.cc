#include <Positionable.h>

#include <Exception.h>

#include <cassert>

namespace Graphics
{

Positionable::Positionable(Positionable &&move) noexcept
{
  *this = std::move(move);
}

auto Positionable::operator=(Positionable &&move) noexcept -> Positionable &
{
  move._parent.lock()->RemoveChild(move.Id);
  _parent = std::move(move._parent);
  move._parent = {};
  _drawArea = std::move(move._drawArea);
  if(!_parent.expired())
    _parent.lock()->AddChild(this);

  return *this;
}

auto Positionable::operator==(const Positionable &other) const -> bool
{
  return Id == other.Id
    && GetAbsoluteDrawArea() == other.GetAbsoluteDrawArea();
}

auto Positionable::AddChild(Positionable *child) -> void
{
  _children.push_back(child);
}

auto Positionable::RemoveChild(uint64_t childId) -> void
{
  const auto &it = std::remove_if(
    _children.begin(),
    _children.end(),
    [childId](Positionable *item)
    {
      return childId == item->Id;
    });

  if(it != _children.end())
    _children.erase(it, _children.end());
}

auto Positionable::SwitchParent(PositionablePointer &parent) -> void
{
  auto parentLocked = _parent.lock();
  if(parentLocked)
    return;

  if(parentLocked)
    parentLocked->RemoveChild(Id);

  _parent = parent;
  if(!_parent.expired())
    _parent.lock()->AddChild(this);
}

auto Positionable::SetPosition(const Utils::Position &position) -> void
{
  _drawArea.position = position;
}

} // namespace Graphics
