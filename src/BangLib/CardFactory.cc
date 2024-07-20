#include <CardFactory.h>

#include <Application.h>
#include <CharacterCard.h>
#include <JsonUtils.h>
#include <PlayCard.h>

#include <Exception.h>

#include <format>
#include <iostream>

namespace
{

constexpr auto cardNumberKey = "cardNumber";
constexpr auto descriptionKey = "description";
constexpr auto NameKey = "name";
constexpr auto numberOfLivesKey = "numberOfLives";
constexpr auto PiecesInDeckKey = "piecesInDeck";
constexpr auto SuitKey = "suit";
constexpr auto TextureNameKey = "textureName";

auto FromJson(const Json::Value& card) -> Bang::CardPointer
{
  std::cout << std::format("Card descriptor: {}", card.toStyledString());

  const auto format = [](const auto& part)
    {
      return std::format("JSON card descriptor didn't contain \"{}\"", part);
    };

  const auto& nameJson = card[::NameKey];
  if (!nameJson.isString())
    throw Utils::Exception{ format(NameKey) };

  const auto& descriptionJson = card[::descriptionKey];
  if (!descriptionJson.isString())
    throw Utils::Exception{ format(descriptionKey) };

  const auto& piecesInDeckJson = card[PiecesInDeckKey];
  if (!piecesInDeckJson.isInt())
    throw Utils::Exception{ format(PiecesInDeckKey) };

  const auto& textureNameJson = card[::TextureNameKey];
  if (!textureNameJson.isString())
    throw Utils::Exception(format(TextureNameKey));

  const auto& numberOfLifesJson = card[::numberOfLivesKey];
  if (numberOfLifesJson.isInt())
  {
    return Bang::CardPointer{
      new Bang::CharacterCard {
        nameJson.asString(),
        descriptionJson.asString(),
        Bang::Application::Get().contentStorageComponent->GetTexture(textureNameJson.asString()),
        numberOfLifesJson.asUInt()} };
  }

  const auto& suitJson = card[::SuitKey];
  const auto& cardNumberJson = card[::cardNumberKey];
  if (suitJson.isInt() && cardNumberJson.isInt())
  {
    return Bang::CardPointer{
      new Bang::PlayCard {
        nameJson.asString(),
        Bang::Application::Get().contentStorageComponent->GetTexture(textureNameJson.asString()),
        static_cast<Bang::CardNumber>(cardNumberJson.asInt()),
        static_cast<Bang::Suit>(suitJson.asInt())} };
  }

  return nullptr;
}

} // namespace

namespace Bang
{

namespace CardFactory
{

auto FromJson(const Json::Value &cards) -> CardPointerVector
{
  if (!cards.isArray())
    throw Utils::Exception{
      std::format("Cards is not an array, rather {}", "")};

  CardPointerVector readCards;
  for (const auto& object : cards)
  {
    if (!object.isObject())
    {
      std::cerr
        << std::format("Non-object found between cards. Type's {}", "")
        << std::endl;

      continue;
    }

    try
    {
      readCards.emplace_back(::FromJson(object));
    }
    catch (const Utils::Exception& e)
    {
      std::cerr
        << std::format("Erroneous card descriptor found: {}. Skipping... ", e.Message())
        << std::endl;
    }
  }

  return readCards;
}

} // namespace CardFactory

} // namespace Bang