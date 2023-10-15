#include <CardBankComponent.h>

#include <Application.h>
#include <JsonFileUtils.h>

#include <fmt/format.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>

namespace
{

constexpr auto characterCardsName = "characterCards.json";
constexpr auto playCardsName = "playCards.json";

auto LoadCardBundle(const std::filesystem::path &bundlePath) -> std::pair<Bang::CardPointerVector, Bang::CardPointerVector>
{
  std::cout << fmt::format("Loading card bundle {}", bundlePath.c_str()) << std::endl;
  const auto characterFilePath = bundlePath / characterCardsName;
  std::cout <<
    fmt::format(
      "Character file path: {} exists: {}",
      characterFilePath.c_str(),
      std::filesystem::exists(characterFilePath)) <<
    std::endl;

  const auto characterCardsCurrent = std::filesystem::exists(characterFilePath)
    ? Bang::LoadFromFile(characterFilePath)
    : Bang::CardPointerVector {};

  const auto playCardFilePath = bundlePath / playCardsName;
  std::cout <<
    fmt::format(
      "Character file path: {} exists: {}",
      playCardFilePath.c_str(),
      std::filesystem::exists(playCardFilePath)) <<
    std::endl;

  const auto playCardsCurrent = std::filesystem::exists(playCardFilePath)
    ? Bang::LoadFromFile(playCardFilePath)
    : Bang::CardPointerVector {};

  return {characterCardsCurrent, playCardsCurrent};
}

auto LoadTexturesForBundle(const std::filesystem::path &bundlePath) -> void
{
  std::cout << fmt::format("Loading textures for \"{}\"", bundlePath.c_str()) << std::endl;
  for (const auto &fileEntry : std::filesystem::directory_iterator {bundlePath})
  {
    if(fileEntry.path().extension() != ".jpg")
      continue;

    std::cout << fmt::format("Loading {}", fileEntry.path().c_str()) << std::endl;
    auto &application = Bang::Application::Get();
    std::cout << "Application instance quired successfully." << std::endl;
    auto &renderingComponent = application.renderingComponent;
    std::cout << "Rendering component: " << renderingComponent.get() << std::endl;
    auto &window = renderingComponent->window;
    std::cout << "Window: " << window.get() << std::endl;
    auto &renderer = window->renderer;
    std::cout << "Renderer: " << renderer.get() << std::endl;
    
    auto *texture = Bang::Application::Get().renderingComponent->window->renderer->LoadImageFromJpg(fileEntry.path());
    std::cout << fmt::format("Storing texture with name: {}", fileEntry.path().stem().c_str()) << std::endl;
    Bang::Application::Get().contentStorageComponent->AddTexture(fileEntry.path().stem().c_str(), texture);
  }
}

}

namespace Bang
{

auto CardBankComponent::LoadAllBanks(const std::string &bankDirectoryPath) -> void
{
  // Load card information from all bundles
  for (auto &bundlePath : std::filesystem::directory_iterator(std::filesystem::path {bankDirectoryPath}))
  {
    if(!bundlePath.is_directory())
      continue;

    std::cout << fmt::format("Loading {}", bundlePath.path().c_str()) << std::endl;
    ::LoadTexturesForBundle(bundlePath);
    const auto &[characters, plays] = ::LoadCardBundle(bundlePath.path());
    characterCards.insert(characterCards.end(), characters.cbegin(), characters.cend());
    playCards.insert(playCards.end(), plays.cbegin(), plays.cend());
  }
}

} // namespace Bang