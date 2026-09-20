#include <CardCollapsingHoveredHighlightingContainer.h>

#include <Debug.h>

namespace Graphics
{

auto CardCollapsingHoveredHighlightingContainer::Handle(
  const Utils::MouseMovementEvent &event) -> void
{
  auto resetZoomedChild = [this]()
  {
    if (_zoomedChild.expired())
      return;
    auto zoomedChild = _zoomedChild.lock();
    if (zoomedChild)
      zoomedChild->SetZoom(1);
    zoomedChild.reset();
  };

  if (!IsPointInDrawArea(this->GetAbsoluteDrawArea(), event.newPos))
  {
    resetZoomedChild();
    return;
  }

  for (auto &child : _children)
  {
    if (IsPointInDrawArea(child->GetAbsoluteDrawArea(), event.newPos))
    {
      if (!_zoomedChild.expired() && _zoomedChild.lock() != child)
        resetZoomedChild();

      _zoomedChild = child;
      auto zoomedChild = _zoomedChild.lock();
      zoomedChild->SetZoom(2);
      return;
    }
  }

}

} // namespace Graphics
