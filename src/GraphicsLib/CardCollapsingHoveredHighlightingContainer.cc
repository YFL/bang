#include <CardCollapsingHoveredHighlightingContainer.h>

namespace Graphics
{

auto CardCollapsingHoveredHighlightingContainer::Handle(
  const Utils::MouseMovementEvent &event) -> void
{
  if (!IsPointInDrawArea(this->GetAbsoluteDrawArea(), event.newPos))
    return;

  for (auto &child : _children)
  {
    if (auto childLocked = child.lock();
      childLocked && IsPointInDrawArea(childLocked->GetAbsoluteDrawArea(), event.newPos))
    {
      std::cout << std::format("Card {} is hovered by the mouse", childLocked->Id) << std::endl;
    }
  }
}

} // namespace Graphics
