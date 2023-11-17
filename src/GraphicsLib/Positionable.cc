#include <Positionable.h>

#include <cassert>

namespace Graphics
{


Positionable::Positionable(Positionable &&move)
{
  *this = std::move(move);
}

auto Positionable::operator=(Positionable &&move) -> Positionable &
{
  _parent = std::move(move._parent);
  move._parent = nullptr;
  _drawArea = std::move(move._drawArea);
  _children = std::move(move._children);
  _childCount = std::move(move._childCount);
  move._childCount = 0;

  return *this;
}

auto Positionable::AddChild(Positionable *child) -> void
{
  _children[child->_drawArea.position.x][child->_drawArea.position.y].emplace_back(child);
  _childCount++;
}

auto Positionable::RemoveChild(Positionable const *child) -> void
{
  const auto &yMap = _children.find(child->_drawArea.position.x);
  if(yMap == _children.end())
    return;

  const auto &positionableVectorIt = yMap->second.find(child->_drawArea.position.y);
  if(positionableVectorIt == yMap->second.end())
    return;

  const auto &newEnd = std::remove(
    std::cbegin(positionableVectorIt->second)
    , std::cend(positionableVectorIt->second)
    , child);
  if(newEnd == std::cend(positionableVectorIt->second))
    return;
  
  const auto removedCount = std::distance(newEnd, std::cend(positionableVectorIt->second));
  assert(removedCount == 1);
  positionableVectorIt->second.erase(newEnd, std::cend(positionableVectorIt->second));
  _childCount -= removedCount;
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

} // namespace Graphics