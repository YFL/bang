#include <CardCollapsingContainer.h>

namespace Graphics
{

auto CardCollapsingContainer::AddChild(Positionable *child) -> void
{
  // The algorithm below works only for cards of the same width.
  /*child->SetPosition({(_children.end() - 1)->first, 0});
  Positionable::AddChild(child);
  const auto childWidth = child->GetDrawArea().w;
  auto positionXOffset = childWidth;
  const auto maxCardsNextToEachOtherWithoutOverlapping = _drawArea.w / childWidth;
  if(_childCount > maxCardsNextToEachOtherWithoutOverlapping)
    positionXOffset =
      childWidth * (maxCardsNextToEachOtherWithoutOverlapping - 1) / (_childCount - 1);

  auto cardIndex = 0;
  for(auto &[x, yMap] : _children)
  {
    for(auto &[y, zVector] : yMap)
    {
      for(auto &card : zVector)
      {
        card->SetPosition({cardIndex * positionXOffset, 0});
      }
    }

    ++cardIndex;
  }*/
}

} // namespace Graphics