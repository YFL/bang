#include <CardCollapsingHoveredHighlightingContainer.h>

namespace Graphics
{

auto CardCollapsingHoveredHighlightingContainer::Handle(
  const Utils::MouseMovementEvent &event) -> void
{
  if (IsPointInDrawArea(this->GetAbsoluteDrawArea(), event.newPos))
  {

  }
}

} // namespace Graphics