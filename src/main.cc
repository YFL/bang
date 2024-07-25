#include <BangLib/Application.h>
#include <BangLib/CreatePlayers.h>
#include <BangLib/GameState.h>
#include <BangLib/GameStates.h>
#include <BangLib/StateManager.h>
#include <SDLUtilsLib/TextUtils.h>

#include <GraphicsLib/CardCollapsingHoveredHighlightingContainer.h>
#include <GraphicsLib/Positionable.h>
#include <GraphicsLib/Screen.h>

#include <fstream>
#include <iostream>
#include <ranges>

namespace
{

constexpr auto WindowWidth = 1920u;
constexpr auto WindowHeight = 1080u;

constexpr auto MaxCardsNextToEachOtherWithoutOverlapping = 8u;
constexpr auto ScreenToCardWidthRatio = 8.5f;
constexpr auto ScreenToCardHeightRatio = 4.f;
constexpr auto ScreenToBottomRowHeightRatio = 36.f;
constexpr auto CardWidth = WindowWidth / ScreenToCardWidthRatio;
constexpr auto CardHeight = WindowHeight / ScreenToCardHeightRatio;
constexpr auto FirstCardToScreenLeftOffset = (WindowWidth - MaxCardsNextToEachOtherWithoutOverlapping * CardWidth) / 2;
constexpr auto BottomRowHeight = WindowHeight / ScreenToBottomRowHeightRatio;

const std::vector<SDL_Rect> PlayerPositions {
  {static_cast<int32_t>(FirstCardToScreenLeftOffset), static_cast<int32_t>(WindowHeight - BottomRowHeight - CardHeight)},
  {static_cast<int32_t>(WindowWidth - CardWidth), static_cast<int32_t>(CardHeight)}
};

constexpr auto CardBundlesDirectoryPath = "./cardBundles";

auto DrawGameState(const std::unique_ptr<Utils::Renderer> &renderer, std::shared_ptr<Graphics::Screen> &mainGameScreen, const Bang::GameState &gameState) -> void
{
  for (auto playerIndex = 0u; playerIndex < gameState.players.size(); ++playerIndex)
  {
    std::cerr << "Drawing player #" << playerIndex << " state." << std::endl;
    const auto& player = gameState.players[playerIndex];
    if (!player)
      throw Utils::Exception{ "Null player found when drawing the game state." };

    const auto& cardsInHand = player->CardsInHand();
    const auto& playerPosition = ::PlayerPositions[playerIndex];

    std::cerr << "Player #" << playerIndex << " position: " << playerPosition.x << ", " << playerPosition.y << std::endl;

    Graphics::CardCollapsingHoveredHighlightingContainer cardCollapsingContainer{
      mainGameScreen.get(),
      Utils::DrawArea {
        {static_cast<int32_t>(::FirstCardToScreenLeftOffset), static_cast<int32_t>(playerPosition.y), 0},
        static_cast<int32_t>(::MaxCardsNextToEachOtherWithoutOverlapping * ::CardWidth),
        static_cast<int32_t>(::CardHeight)} };

    const auto cardCollapsingContainerDrawArea = cardCollapsingContainer.GetDrawArea();
    std::cerr << std::format("CardCollapsingContainer drawArea: {}", ToString(cardCollapsingContainerDrawArea)) << std::endl;

    std::vector<Graphics::Positionable> positionables;
    positionables.reserve(10);
    for (auto cardIndex = 0u; cardIndex < cardsInHand.size(); ++cardIndex)
    {
      positionables.emplace_back(&cardCollapsingContainer, Utils::DrawArea{ {}, static_cast<int32_t>(::CardWidth), static_cast<int32_t>(::CardHeight) });
    }

    auto cardIndex = 0u;
    std::ranges::for_each(positionables, [&cardIndex, &renderer, &cardsInHand](const Graphics::Positionable& positionable)
      {
        const auto& cardPosition = Utils::DrawAreaToSDLRect(positionable.GetAbsoluteDrawArea());
        std::cerr << "Card #" << cardIndex << " position: " << cardPosition.x << ", " << cardPosition.y << ", " << cardPosition.w << ", " << cardPosition.h << std::endl;
        renderer->RenderTexture(cardsInHand[cardIndex]->Texture(), nullptr, &cardPosition);
        std::cerr << " Card #" << cardIndex++ << " drawn." << std::endl;
      });

    std::cerr << "Drawing player #" << playerIndex << "'s character." << std::endl;
    auto* character = player->Character();
    if (!character)
    {
      std::cerr << "No character available." << std::endl;
      return;
    }

    const SDL_Rect characterPosition{
      playerPosition.x,
      playerPosition.y - static_cast<int32_t>(::CardHeight),
      static_cast<int32_t>(::CardWidth),
      static_cast<int32_t>(::CardHeight)
    };

    std::cerr << "Character position: " << characterPosition.x << ", " << characterPosition.y << ", " << characterPosition.w << ", " << characterPosition.h << std::endl;
    renderer->RenderTexture(character->Texture(), nullptr, &characterPosition);
    std::cerr << "Drawing player #" << playerIndex << "'s character finished." << std::endl;
  }
}

} // namespace

#undef main

auto main() -> int
{
  try
  {
    auto &application = Bang::Application::Get();
    application.renderingComponent->Init(
      ::WindowWidth,
      ::WindowHeight,
      "Bang",
      application.inputComponent);
    // Loading the card banks requires a renderer.
    std::cout << "Loading card banks." << std::endl;
    application.cardBankComponent->LoadAllBanks(::CardBundlesDirectoryPath);

    const auto fontName = "./font.ttf";
    std::cout << "Loading font." << std::endl;
    auto *font = Utils::LoadFontFromFile(fontName, 180u);
    if(!font)
      throw Utils::Exception {""};

    std::cout << "Adding font to content storage: " << fontName << " " << font << std::endl;
    application.contentStorageComponent->AddFont(fontName, font);

    std::cout << "Creating state manager with CreatePlayers initial state." << std::endl;
    Bang::StateManager stateManager {
      std::unique_ptr<Bang::State<GameStates>> {new Bang::CreatePlayers}};

    Bang::GameState gameState;

    SDL_Event event {};
    auto &renderer = application.renderingComponent->window->renderer;
    while(event.type != SDL_QUIT)
    {
      std::cerr << "Polling events." << std::endl;
      if(SDL_PollEvent(&event))
      {
        if(event.type == SDL_QUIT)
          break;
        if(event.type == SDL_KEYDOWN)
        {
          if(event.key.keysym.sym == SDLK_ESCAPE)
            break;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
        {
          const auto &button = event.button;
          static std::ofstream buttonClicks { "buttonClicks.txt" };
          buttonClicks
            << std::format(
              "button: {} clicks: {} state: {} timestamp: {} x: {} y: {} windowId: {} which: {}",
              button.button,
              button.clicks,
              button.state,
              button.timestamp,
              button.x,
              button.y,
              button.windowID,
              button.which)
            << std::endl;

          application.inputComponent->mouse.Handle(static_cast<SDL_MouseButtonEvent>(
            event.button));
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
          application.inputComponent->mouse.Handle(static_cast<SDL_MouseMotionEvent>(
            event.motion));
        }
      }

      std::cerr << "Event polling finished." << std::endl;
      std::cerr << "Updating the state manager." << std::endl;
      stateManager.Update(gameState);
      std::cerr << "State manager updated." << std::endl;

      std::cerr << "Clearing renderer." << std::endl;
      renderer->ClearRenderer(SDL_Color {0, 0, 0, 255});
      std::cerr << "Renderer cleared." << std::endl;

      std::cerr << "Drawing the game state." << std::endl;
      ::DrawGameState(renderer, application.renderingComponent->screen, gameState);
      std::cerr << "Drawing finished" << std::endl;

      std::cerr << "Presenting the rendered frame." << std::endl;
      renderer->RenderPresent();
      std::cerr << "Presenting finished." << std::endl;
    }
  }
  catch(const Utils::Exception &e)
  {
    std::cerr << e.Message() << std::endl;
    return -1;
  }

  return 0;
}