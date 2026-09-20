#include <CardCollapsingContainer.h>

namespace Graphics
{

auto CardCollapsingContainer::AddCard(const PositionablePointer &child) -> void
{
  std::cerr << "Adding card to CardCollapsingContainer." << std::endl;
  // The algorithm below works only for cards of the same width.
  const auto childWidth = child->GetDrawArea().size.x;
  std::cerr << "Child width: " << childWidth << std::endl;
  std::cerr << "Children count: " << _children.size() << std::endl;
  std::cerr << "Draw area width: " << _drawArea.size.x << std::endl;
  // Move new card to the right next to the rightmost card - without any overlapping (basic case).
  child->SetPosition({static_cast<int32_t>((_children.size() - 1) * childWidth), 0});

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
      [&cardIndex, horizontalOffsetBetweenCards](PositionablePointer &card)
      {
        card->SetPosition(
          { cardIndex++ * static_cast<int32_t>(horizontalOffsetBetweenCards), 0 });
      });
  }
}

auto CardCollapsingContainer::AddChild(const PositionablePointer &child) -> void
{
  Positionable::AddChild(child);
  AddCard(child);
}

} // namespace Graphics
