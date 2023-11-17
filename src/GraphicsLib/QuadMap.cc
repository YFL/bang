#include <QuadMap.h>

#include <optional>

namespace
{

const std::unordered_map<int32_t, int32_t> Quarters = 
{
  {0, 1},
  {1, 2},
  {2, 4},
  {3, 8},
  {-1, 0}
};

constexpr auto AllQuarters = 15;

inline auto IsSingleQuarter(const int32_t quarters) -> std::optional<bool>
{
  if (!quarters)
    return std::nullopt;

  auto quarterCount = 0u;
  for (const auto &[key, value] : ::Quarters)
  {
    if(quarters & value)
      ++quarterCount;

    if(quarterCount > 1)
      return false;
  }

  return true;
}

} // namespace 

namespace Graphics
{

QuadMapNode::QuadMapNode(const DrawArea &drawArea, QuadMapNode *parent)
  : _parent {parent}
  , _drawArea {drawArea}
{
  if (drawArea.w < 2 || drawArea.h < 2)
    return;
  
  const auto rowCount = 2;
  const auto columnCount = rowCount;
  for (auto row = 0u; row < rowCount; ++row)
  {
    auto childDrawArea = drawArea;
    childDrawArea.w = drawArea.w / columnCount;
    childDrawArea.h = drawArea.h / rowCount;
    for (auto column = 0u; column < columnCount; ++column)
    {
      // We add column to the resulting x, so that the two columns don't share a line of a single
      // pixel. The same goes for the y calculation but with row.
      childDrawArea.position.x = column * drawArea.w / columnCount + column;
      childDrawArea.position.y = row * drawArea.h / rowCount + row;
      _childNodes[row * rowCount + column] = QuadMapNode {childDrawArea, this};
    }
  }
}

QuadMapNode::QuadMapNode(QuadMapNode &&move)
{
  *this = std::move(move);
}

auto QuadMapNode::operator=(QuadMapNode &&move) -> QuadMapNode &
{
  _parent = std::move(move._parent);
  move._parent = nullptr;
  _drawArea = std::move(move._drawArea);
  _childNodes = std::move(move._childNodes);
  _childElements = std::move(move._childElements);

  return *this;
}

auto QuadMapNode::Add(Positionable *element) -> void
{
  if (!DoDrawAreasCollide(_drawArea, element->GetAbsoluteDrawArea()))
    return;

  const auto quarters = GetQuarters(element);
  // quarters == 0 should mean, that:
  // a) the element is outside of the draw area of this (no collision),
  // c) the element won't fit into any of the child nodes,
  // b) there aren't any child nodes.
  if (!quarters)
  {
    _childElements.push_back(element);
    return;
  }

  for (auto i = 0u; i < ChildNodeCount; ++i)
   if (quarters & ::Quarters.at(i))
    _childNodes[i].Add(element);
}

auto QuadMapNode::Remove(Positionable *element) -> void
{

}

auto QuadMapNode::GetQuarters(Positionable const *element) const -> int32_t
{
  const auto elementDrawArea = element->GetAbsoluteDrawArea();
  if (!DoDrawAreasCollide(elementDrawArea, _drawArea))
    return ::Quarters.at(-1);

  auto quarters = 0;
  for (auto i = 0; i < ChildNodeCount && i < _childNodes.size(); ++i)
    if (DoesDrawAreaFitAnother(elementDrawArea, _childNodes[i]._drawArea))
      quarters |= ::Quarters.at(i);

  return quarters;
}

} // namespace Graphics