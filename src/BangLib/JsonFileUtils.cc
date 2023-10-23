#include "BangLib/JsonFileUtils.h"

#include "BangLib/Application.h"
#include "BangLib/CharacterCard.h"
#include "BangLib/Exception.h"
#include "BangLib/PlayCard.h"

#include <fmt/format.h>

#include <json/json.h>

#include <fstream>
#include <iostream>

namespace
{

constexpr auto cardNumberKey = "cardNumber";
constexpr auto descriptionKey = "description";
constexpr auto NameKey = "name";
constexpr auto numberOfLifesKey = "numberOfLifes";
constexpr auto PiecesInDeckKey = "piecesInDeck";
constexpr auto SuitKey = "suit";
constexpr auto TextureNameKey = "textureName";

auto ReadJsonFromFile(const std::string &pathToFile) -> Json::Value
{
  std::ifstream file(pathToFile);
  if(!file.is_open())
    throw Bang::Exception {fmt::format("File {} coudln't be opened to read json,", pathToFile)};
  
  Json::Reader r;
  Json::Value jsonRoot;
  if(!r.parse(file, jsonRoot, false))
    throw Bang::Exception {fmt::format("File {} didn't contain valid json.", pathToFile)};

  return jsonRoot;
}

auto JsonToCardPointer(const Json::Value &jsonObject) -> Bang::CardPointer
{
  const auto format = [](const auto &part)
  { return fmt::format("JSON card descriptor didn't contain \"{}\"", part); };

  const auto &nameJson = jsonObject[::NameKey];
  if(!nameJson.isString())
    throw Bang::Exception {format(NameKey)};
  
  const auto &descriptionJson = jsonObject[::descriptionKey];
  if(!descriptionJson.isString())
    throw Bang::Exception {format(descriptionKey)};

  const auto &piecesInDeckJson = jsonObject[PiecesInDeckKey];
  if(!piecesInDeckJson.isInt())
    throw Bang::Exception {format(PiecesInDeckKey)};

  const auto &textureNameJson = jsonObject[::TextureNameKey];
  if(!textureNameJson.isString())
    throw Bang::Exception(format(TextureNameKey));

  const auto &numberOfLifesJson = jsonObject[::numberOfLifesKey];
  if(numberOfLifesJson.isInt())
  {
    return Bang::CardPointer {
      new Bang::CharacterCard {
        nameJson.asString(),
        descriptionJson.asString(),
        Bang::Application::Get().contentStorageComponent->GetTexture(textureNameJson.asString()),
        numberOfLifesJson.asUInt()}};
  }

  const auto &suitJson = jsonObject[::SuitKey];
  const auto &cardNumberJson = jsonObject[::cardNumberKey];
  if(suitJson.isInt() && cardNumberJson.isInt())
  {
    return Bang::CardPointer {
      new Bang::PlayCard {
        nameJson.asString(),
        Bang::Application::Get().contentStorageComponent->GetTexture(textureNameJson.asString()),
        static_cast<Bang::CardNumber>(cardNumberJson.asInt()),
        static_cast<Bang::Suit>(suitJson.asInt())}};
  }

  return nullptr;
}

} // namespace

namespace Bang
{

auto LoadFromFile(const std::string &pathToFile) -> CardPointerVector
{
  const auto jsonRoot = ::ReadJsonFromFile(pathToFile);
  if(!jsonRoot.isArray())
    throw Exception {fmt::format("File \"{}\" didn't contain an array as it's root element.", pathToFile)};

  CardPointerVector readCards;
  for(const auto &object : jsonRoot)
  {
    if(!object.isObject())
    {
      std::cerr << fmt::format("Non object found in root of \"{}\" file. Skipping...", pathToFile) << std::endl;
      continue;
    }

    try
    {
      readCards.emplace_back(JsonToCardPointer(object));
    }
    catch(const Exception &e)
    {
      std::cerr << fmt::format("Erroneous card descriptor found: {}. Skipping... ", e.Message()) << std::endl;
    }
  }

  return readCards;
}


} // namespace Bang