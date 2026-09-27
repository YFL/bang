#include <CardCollapsingContainer.h>

namespace Bang
{

auto CardCollapsingContainer::AddCard(const Bang::CardWeakPtr &card) -> void
{
  std::cerr << "Adding card to CardCollapsingContainer." << std::endl;
  auto cardLocked = card.lock();
  if (!cardLocked)
  {
    std::cerr << "Child is expired." << std::endl;
    return;
  }

  auto cardPositionable = cardLocked->Entity()->Get<Graphics::Positionable>();
  if (!cardPositionable)
  {
    std::cerr << "Child has no Positionable component." << std::endl;
    return;
  }

  AddChild(cardPositionable);
  std::cerr << "Added card's positionable as child to CardCollapsingContainer." << std::endl;
  // The algorithm below works only for cards of the same width.
  const auto childWidth = cardPositionable->GetDrawArea().size.x;
  std::cerr << "Child width: " << childWidth << std::endl;
  std::cerr << "Children count: " << _children.size() << std::endl;
  std::cerr << "Draw area width: " << _drawArea.size.x << std::endl;
  // Move new card to the right next to the rightmost card - without any overlapping (basic case).
  // TODO: Test if this works with only as many cards in the container as can fit it without
  // overlapping.
  cardPositionable->SetPosition({static_cast<int32_t>((_children.size() - 1) * childWidth), 0});

  const auto maxCardsNextToEachOtherWithoutOverlapping = std::max(1.f, static_cast<float>(_drawArea.size.x) / childWidth);
  if (_children.size() > maxCardsNextToEachOtherWithoutOverlapping)
  {
    const auto absoluteArea = GetAbsoluteDrawArea();
    // Overflow handling
    // When there are more cards in the container than it can position next to each other without
    // overlapping, we calculate the offset between the cards based on the with of the container
    // and the number of stored cards.
    const auto horizontalOffsetBetweenCards = _children.size() != 1
      ? (absoluteArea.size.x * absoluteArea.zoom - childWidth) / (_children.size() - 1)
      : 0;

    std::cerr << "Horizontal offset between cards: " << horizontalOffsetBetweenCards << std::endl;

    auto cardIndex = 0;
    std::ranges::for_each(
      _children,
      [&cardIndex, horizontalOffsetBetweenCards](Graphics::PositionableWeakPtr &card)
      {
        if (card.expired())
          return;
        card.lock()->SetPosition(
          { cardIndex++ * static_cast<int32_t>(horizontalOffsetBetweenCards), 0 });
      });
  }
}

auto CardCollapsingContainer::Handle(
  const Utils::MouseButtonEvent &event) -> void
{
  // We are relying on the zoomed child being set in the mouse movement event handler, operating
  // under the assumption that the mouse movement event handler is called before the mouse button
  // event handler.
  // This might not be a great idea, but it is the simplest solution for now.
  if (_hoveredChild.expired())
    return;
  if (!event.down || event.button != Utils::mouseLeftButton)
    return;
  const auto positionable = _hoveredChild.lock()->Entity()->Get<Graphics::Positionable>();
  if (!Utils::IsPointInDrawArea(positionable->GetAbsoluteDrawArea(), event.position))
    return;
  IEventEmitter<CardSelected>::Emit({ _hoveredChild });
}

auto CardCollapsingContainer::Handle(
  const Utils::MouseMovementEvent &event) -> void
{
  auto resetHoveredChild = [this]()
    {
      if (_hoveredChild.expired())
        return;
      _hoveredChild.reset();
      // End of hover signal
      Utils::IEventEmitter<CardHovered>::Emit({ {} });
    };

  if (!Utils::IsPointInDrawArea(this->GetAbsoluteDrawArea(), event.newPos))
  {
    resetHoveredChild();
    return;
  }

  std::cerr << "Testing cards." << std::endl;
  for (auto &card : _cards)
  {
    auto cardLocked = card.lock();
    if (!cardLocked)
    {
      std::cerr << "Card is expired." << std::endl;
      continue;
    }

    auto cardPositionable = cardLocked->Entity()->Get<Graphics::Positionable>();
    if (Utils::IsPointInDrawArea(cardPositionable->GetAbsoluteDrawArea(), event.newPos))
    {
      if (!_hoveredChild.expired() && _hoveredChild.lock() != cardLocked)
        resetHoveredChild();

      _hoveredChild = card;
      IEventEmitter<CardHovered>::Emit({ card });
      return;
    }
  }

  // In case the mouse is inside the draw area but no card is hovered.
  resetHoveredChild();

}

} // namespace Bang
