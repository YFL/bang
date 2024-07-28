#include <Positionable.h>

#include <Exception.h>

#include <ranges>

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
    _parent.lock()->AddChild(shared_from_this());

  return *this;
}

auto Positionable::operator==(const Positionable &other) const -> bool
{
  return Id == other.Id && GetAbsoluteDrawArea() == other.GetAbsoluteDrawArea();
}

auto Positionable::AddChild(const std::shared_ptr<Positionable> &child) -> void
{
  _children.push_back(child);
}

auto Positionable::RemoveChild(uint64_t childId) -> void
{
  const auto &[deleteFirst, deleteLast] = std::ranges::remove_if(
    _children,
    [childId](const PositionableWeakPtr &item)
    {
      const auto itemLocked = item.lock();
      return !itemLocked && childId == itemLocked->Id;
    });

  _children.erase(deleteFirst, deleteLast);
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
    _parent.lock()->AddChild(shared_from_this());
}

auto Positionable::SetPosition(const Utils::Position &position) -> void
{
  _drawArea.position = position;
}

} // namespace Graphics
