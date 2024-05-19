#include <CardCollapsingContainer.h>
#include <ranges>

namespace Graphics
{

auto CardCollapsingContainer::AddCard(Positionable *child) -> void
{
  // The algorithm below works only for cards of the same width.
  const auto childWidth = child->GetDrawArea().w;
  // Move new card to the right next to the rightmost card - without any overlapping (basic case).
  child->SetPosition({static_cast<int32_t>((_children.size() - 1) * childWidth), 0});
  
  const auto maxCardsNextToEachOtherWithoutOverlapping = _drawArea.w / childWidth;
  if (_children.size() > maxCardsNextToEachOtherWithoutOverlapping)
  {
    // Overflow handling
    // When there are more cards in the container than it can position next to each other without
    // overlapping, we calculate the offset between the cards based on the with of the container
    // and the number of stored cards.
    const auto verticalOffsetBetweenCards =
      childWidth * (maxCardsNextToEachOtherWithoutOverlapping - 1) / (_children.size() - 1);

    std::cerr << "Vertical offset between cards: " << verticalOffsetBetweenCards << std::endl;

    auto cardIndex = 0;
    std::ranges::for_each(
      _children,
      [&cardIndex, /*positionXOffset, */verticalOffsetBetweenCards](Positionable* card)
      {
        card->SetPosition({ cardIndex++ * static_cast<int32_t>(verticalOffsetBetweenCards), 0 });
      });
  }
}

auto CardCollapsingContainer::AddChild(Positionable* child) -> void
{
  Positionable::AddChild(child);
  AddCard(child);
}

} // namespace Graphics