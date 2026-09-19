#include <CardCollapsingHoveredHighlightingContainer.h>

#include <Debug.h>

namespace Graphics
{

auto CardCollapsingHoveredHighlightingContainer::Handle(
  const Utils::MouseMovementEvent &event) -> void
{
  static auto zoomedChild = PositionablePointer{};
  auto resetZoomedChild = [](PositionablePointer& zoomedChild)
  {
    if (zoomedChild)
      zoomedChild->SetZoom(1);
    zoomedChild.reset();
  };

  if (!IsPointInDrawArea(this->GetAbsoluteDrawArea(), event.newPos))
  {
    resetZoomedChild(zoomedChild);
    return;
  }

  for (auto &child : _children)
  {
    if (IsPointInDrawArea(child->GetAbsoluteDrawArea(), event.newPos))
    {
      std::cout << std::format("Card {} is hovered by the mouse", child->Id.str()) << std::endl;
      if (zoomedChild && zoomedChild != child)
        resetZoomedChild(zoomedChild);
      zoomedChild = child;
      zoomedChild->SetZoom(2);
      return;
    }
  }

}

} // namespace Graphics
