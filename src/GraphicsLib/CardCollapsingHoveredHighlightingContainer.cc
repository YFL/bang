#include <CardCollapsingHoveredHighlightingContainer.h>

#include <Debug.h>

namespace Graphics
{

auto CardCollapsingHoveredHighlightingContainer::Handle(
  const Utils::MouseMovementEvent &event) -> void
{
  if (!IsPointInDrawArea(this->GetAbsoluteDrawArea(), event.newPos))
    return;

  for (auto &child : _children)
  {
    if (child && IsPointInDrawArea(child->GetAbsoluteDrawArea(), event.newPos))
    {
      std::cout << std::format("Card {} is hovered by the mouse", child->Id.str()) << std::endl;
      child->SetSize(child->GetDrawArea().size * 2);
    }
  }
}

} // namespace Graphics
