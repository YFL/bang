#pragma once

#include <IdFul.h>

#include <guid.hpp>

#include <unordered_map>

namespace Utils
{

template <typename T>
auto ComponentId() -> xg::Guid
{
  const static auto id = xg::newGuid();
  return id;
}

class Entity;

using EntityPointer = std::shared_ptr<Entity>;
using EntityWeakPtr = std::weak_ptr<Entity>;

class Component : public IdFul
{
public:
  Component(const EntityPointer &parent) : IdFul{}, _parent { parent }
  {}
  virtual ~Component() = default;
  Component(const Component &copy) = delete;
  Component(Component &&move) noexcept
    : IdFul{ move }, _parent { move._parent }
  {}

public:
  auto operator=(const Component &copy) -> Component & = delete;
  auto operator=(Component &&move) noexcept -> Component & = delete;

public:
  auto Parent() const -> EntityPointer
  { return _parent.lock(); }

private:
  const EntityWeakPtr _parent;
};

using ComponentPointer = std::shared_ptr<Component>;

class Entity : public IdFul, public std::enable_shared_from_this<Entity>
{
public:
  Entity() : IdFul{}
  {}
  virtual ~Entity() = default;
  Entity(const Entity &copy) = delete;
  Entity(Entity &&move) noexcept
    : IdFul{move}
    , _ownedComponents{ std::move(move._ownedComponents) }
  {}

public:
  auto operator=(const Entity &copy) -> Entity & = delete;
  auto operator=(Entity &&move) -> Entity & = delete;

public:

public:
  template <typename ComponentT>
  auto Has() const -> bool
  { return _ownedComponents.find(ComponentId<ComponentT>()) != std::end(_ownedComponents); }

  //! Since every component has to have a parent, which is the first parameter into the constructor
  //! this function provides it when creating the component, so the parent argument for the
  //! component constructor MUST NOT be provided when calling this function.
  template <typename ComponentT, typename ...Args>
  auto AddComponent(Args &&...args) -> void
  {
    _ownedComponents.insert(
      {
        ComponentId<ComponentT>(),
        ComponentPointer{ new ComponentT{ shared_from_this(), std::forward<Args>(args)... } }
      });
  }

  template <typename ComponentT>
  auto Get() const -> std::shared_ptr<ComponentT>
  {
    return Has<ComponentT>()
      ? dynamic_pointer_cast<ComponentT>(_ownedComponents.at(ComponentId<ComponentT>()))
      : nullptr;
  }

  template <typename ComponentT>
  auto RemoveComponent() -> void
  { _ownedComponents.erase(ComponentId<ComponentT>()); }

private:
  std::unordered_map<xg::Guid, ComponentPointer> _ownedComponents;
};

} // namespace Utils