#include <Deck.h>

#include <Application.h>

#include <CardCollapsingContainer.h>

#include <random>

namespace Bang
{

Deck::Deck()
{
  const auto cardSize = Application::Get().configComponent->CardSize();
  auto cardCollapsingContainer = std::make_shared<CardCollapsingContainer>(
    nullptr,
    Utils::DrawArea{ {0, 0, 0}, Utils::ConvertTo(cardSize, Utils::LengthUnits::px) });
  _entity->AddComponent<Graphics::Positionable>(
    std::dynamic_pointer_cast<Graphics::Positionable>(cardCollapsingContainer));
}

auto Deck::AddCard(const CardPointer &card) -> void
{
  _cards.emplace_back(card);
  auto cardPositionable = card->Entity()->Get<Graphics::Positionable>();
  auto deckPositionable = _entity->Get<Graphics::Positionable>();
  if (cardPositionable && deckPositionable)
    deckPositionable->AddChild(cardPositionable);
}

auto Deck::GetCard() -> CardWeakPtr
{
  if (_cards.empty())
    return {};
  auto card = _cards.back();
  _cards.pop_back();
  return card;
}

auto Deck::Shuffle() -> void
{
  std::shuffle(
    _cards.begin(),
    _cards.end(),
    std::mt19937{ std::random_device{}() });
}

auto Deck::Handle(const CardSelected &event) -> void
{
  if (event.card.expired())
  {
    std::cerr << "Selected card has expired." << std::endl;
    return;
  }

  auto card = event.card.lock();

  const auto newEnd = std::remove_if(
    _cards.begin(),
    _cards.end(),
    [&card](const CardWeakPtr &cardInDeck)
    {
      return cardInDeck.lock() == card;
    });
  _cards.erase(newEnd, _cards.end());
  card->Entity()->Get<Graphics::Positionable>()->SwitchParent({});
  Utils::IEventEmitter<CardSelected>::Emit({ card });
}

} // namespace Bang