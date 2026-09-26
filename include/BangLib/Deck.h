#pragma once

#include <Card.h>

#include <ECS.h>
#include <EventHandler.h>

#include <Mouse.h>

namespace Bang
{

class Deck
  : public Utils::IEventHandler<Utils::MouseButtonEvent>
  , public Utils::IEventHandler<Utils::MouseMovementEvent>
{
public:
  Deck();
  Deck(const Deck &) = default;
  Deck(Deck &&) = default;
  virtual ~Deck() = default;

public:
  auto operator=(const Deck &) -> Deck & = default;
  auto operator=(Deck &&) -> Deck & = default;

public:
  auto AddCard(const CardPointer &card) -> void;
  auto GetCard() -> CardWeakPtr;
  auto Shuffle() -> void;

public:
  auto Entity() const -> const Utils::EntityPointer
  { return _entity; }

  auto Entity() -> Utils::EntityPointer
  { return _entity; }

public:
  auto Handle(const Utils::MouseButtonEvent &event) -> void override;
  auto Handle(const Utils::MouseMovementEvent &event) -> void override;

private:
  CardWeakPtrVector _cards;
  Utils::EntityPointer _entity = std::make_shared<Utils::Entity>();
};

using DeckPointer = std::shared_ptr<Deck>;
using DeckWeakPtr = std::weak_ptr<Deck>;

} // namespace Bang