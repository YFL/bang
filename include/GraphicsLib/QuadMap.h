#pragma once

#include <Positionable.h>

#include <map>
#include <unordered_map>

namespace Graphics
{

class QuadMapNode
{
private:
  static constexpr auto ChildNodeCount = 4u;
public:
  QuadMapNode() = default;
  QuadMapNode(const DrawArea &drawArea, QuadMapNode *parent = nullptr);
  QuadMapNode(const QuadMapNode &) = delete;
  QuadMapNode(QuadMapNode &&move);

public:
  auto operator=(const QuadMapNode &) -> QuadMapNode & = delete;
  auto operator=(QuadMapNode &&move) -> QuadMapNode &;

public:
  auto Add(Positionable *element) -> void;
  auto Remove(Positionable *element) -> void;

private:
  /**
   * Returns a bitmask of the quarters where the element fits.
  */
  auto GetQuarters(Positionable const *element) const -> int32_t;

private:
  QuadMapNode *_parent = nullptr;
  DrawArea _drawArea = {};
  //! If there aren't any child nodes, it means, that the drawArea of this is too small to be
  //! divided further, i.e. this is a leaf node.
  std::vector<QuadMapNode> _childNodes = {};
  std::vector<Positionable *> _childElements = {};
};

class QuadMap
{
public:
  QuadMap(const DrawArea &drawArea);

public:
  auto Add(Positionable *element) -> void;
  auto Remove(Positionable *element) -> void;
  auto GetTopMostElementAt(const Position &position) -> Positionable *;

private:
  // Each depth has a separate QuadMap available.
  std::map<int32_t, QuadMapNode> _maps;
};

} // namespace Graphics