#include <CardBankComponent.h>

#include <Application.h>
#include <JsonFileUtils.h>

#include <format>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>

namespace
{

constexpr auto characterCardsName = "characterCards.json";
constexpr auto playCardsName = "playCards.json";

auto LoadCardBundle(const std::filesystem::path &bundlePath)
  -> std::pair<Bang::CardPointerVector, Bang::CardPointerVector>
{
  std::cout << std::format("Loading card bundle {}", bundlePath.string()) << std::endl;
  const auto characterFilePath = bundlePath / characterCardsName;
  std::cout
    << std::format(
      "Character file path: {} exists: {}",
      characterFilePath.string(),
      std::filesystem::exists(characterFilePath))
    << std::endl;

  const auto characterCardsCurrent = std::filesystem::exists(characterFilePath)
    ? Bang::LoadFromFile(characterFilePath.string())
    : Bang::CardPointerVector {};

  const auto playCardFilePath = bundlePath / playCardsName;
  std::cout
    << std::format(
      "Character file path: {} exists: {}",
      playCardFilePath.string(),
      std::filesystem::exists(playCardFilePath))
    << std::endl;

  const auto playCardsCurrent = std::filesystem::exists(playCardFilePath)
    ? Bang::LoadFromFile(playCardFilePath.string())
    : Bang::CardPointerVector {};

  return {characterCardsCurrent, playCardsCurrent};
}

auto LoadTexturesForBundle(const std::filesystem::path &bundlePath) -> void
{
  std::cout << std::format("Loading textures for \"{}\"", bundlePath.string()) << std::endl;
  for (const auto &fileEntry : std::filesystem::directory_iterator {bundlePath})
  {
    if(fileEntry.path().extension() != ".jpg")
      continue;

    std::cout << std::format("Loading {}", fileEntry.path().string()) << std::endl;
    auto &application = Bang::Application::Get();
    std::cout << "Application instance quired successfully." << std::endl;
    auto &renderingComponent = application.renderingComponent;
    std::cout << "Rendering component: " << renderingComponent.get() << std::endl;
    auto &window = renderingComponent->window;
    std::cout << "Window: " << window.get() << std::endl;
    auto &renderer = window->renderer;
    std::cout << "Renderer: " << renderer.get() << std::endl;
    
    auto *texture = Bang::Application::Get().renderingComponent->window->renderer->LoadImageFromJpg(
      fileEntry.path().string());
    
    std::cout
      << std::format("Storing texture with name: {}", fileEntry.path().stem().string())
      << std::endl;
    
    Bang::Application::Get().contentStorageComponent->AddTexture(
      fileEntry.path().stem().string(),
      texture);
  }
}

}

namespace Bang
{

auto CardBankComponent::LoadAllBanks(const std::string &bankDirectoryPath) -> void
{
  const std::filesystem::path path(bankDirectoryPath);
  // Load card information from all bundles
  for (auto &bundlePath : std::filesystem::directory_iterator(path))
  {
    if(!bundlePath.is_directory())
      continue;

    std::cout << std::format("Loading {}", bundlePath.path().string()) << std::endl;
    ::LoadTexturesForBundle(bundlePath);
    const auto &[characters, plays] = ::LoadCardBundle(bundlePath.path());
    characterCards.insert(characterCards.end(), characters.cbegin(), characters.cend());
    playCards.insert(playCards.end(), plays.cbegin(), plays.cend());
  }
}

} // namespace Bang