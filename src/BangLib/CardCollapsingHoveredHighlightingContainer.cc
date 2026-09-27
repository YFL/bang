#include <CardCollapsingHoveredHighlightingContainer.h>

#include <Debug.h>

namespace Bang
{

auto CardCollapsingHoveredHighlightingContainer::Handle(const CardHovered &event) -> void
{
  auto card = event.card.lock();
  auto zoomedChild = _zoomedChild.lock();
  auto zoomedCardPositionable = _zoomedChild.expired()
    ? nullptr
    : zoomedChild->Entity()->Get<Graphics::Positionable>();
  if (card && card == zoomedChild)
    return;

  if (zoomedCardPositionable)
    zoomedCardPositionable->SetZoom(1);

  _zoomedChild = event.card;
  if (card)
    card->Entity()->Get<Graphics::Positionable>()->SetZoom(2);
}

} // namespace Bang
