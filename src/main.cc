#include <BangLib/Application.h>
#include <BangLib/CreateDeck.h>
#include <BangLib/GameState.h>
#include <BangLib/GameStates.h>
#include <BangLib/StateManager.h>
#include <SDLUtilsLib/TextUtils.h>

#include <GraphicsLib/CardCollapsingHoveredHighlightingContainer.h>
#include <GraphicsLib/Positionable.h>
#include <GraphicsLib/Screen.h>

#include <array>
#include <fstream>
#include <iostream>

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

constexpr auto FontName = "./WesternBangBang-Regular.ttf";

const Bang::PlayerPositionVector PlayerPositions {
  Utils::DrawArea {
    {
      static_cast<int32_t>(FirstCardToScreenLeftOffset),
      static_cast<int32_t>(WindowHeight - BottomRowHeight - CardHeight),
      0
    },
    {
      static_cast<uint32_t>(::CardWidth),
      static_cast<uint32_t>(::CardHeight),
      Utils::LengthUnits::px
    }
  },
  {
    {
      static_cast<int32_t>(WindowWidth - CardWidth),
      static_cast<int32_t>(CardHeight),
      0
    },
    {
      static_cast<uint32_t>(::CardWidth),
      static_cast<uint32_t>(::CardHeight),
      Utils::LengthUnits::px
    }
  }
};

constexpr auto CardBundlesDirectoryPath = "./cardBundles";

auto DrawGameState(const std::unique_ptr<Utils::Renderer> &renderer, std::shared_ptr<Graphics::Screen> &mainGameScreen, const Bang::GameState &gameState) -> void
{
  const auto &app = Bang::Application::Get();
  const auto &playerPositions = app.configComponent->PlayerPositions();
  const auto colors = std::array<SDL_Color, 2>{
    SDL_Color { 0, 255, 0, 255 },
    SDL_Color { 0, 0, 255, 255 }
  };
  for (auto playerIndex = 0u; playerIndex < gameState.players.size(); ++playerIndex)
  {
    const auto &playerPosition = playerPositions[playerIndex];
    std::cerr << "Drawing player #" << playerIndex << " state." << std::endl;
    const auto &player = gameState.players[playerIndex];
    if (!player)
      throw Utils::Exception{ "Null player found when drawing the game state." };

    std::cerr << "Drawing player #" << playerIndex << "'s character." << std::endl;
    const auto character = player->Character().lock();
    if (!character)
    {
      std::cerr << "Character is not available; continue" << std::endl;
      continue;
    }

    const auto characterPosition = Utils::DrawAreaToSDLRect(
      character->Entity()->Get<Graphics::Positionable>()->GetAbsoluteDrawArea());
    renderer->RenderTexture(character->Texture(), nullptr, &characterPosition);

    for (const auto& cardWeakPtr : player->CardsInHand())
    {
      const auto card = cardWeakPtr.lock();
      if (!card)
      {
        std::cerr << "Card is not available; continue" << std::endl;
        continue;
      }

      const auto cardDrawArea =
        card->Entity()->Get<Graphics::Positionable>()->GetAbsoluteDrawArea();
      const auto cardPosition = Utils::DrawAreaToSDLRect(cardDrawArea);

      std::cerr << "player index: " << playerIndex << " card position: " << cardPosition.x << ", " << cardPosition.y << std::endl;
      auto debugRectPos = cardPosition;
      renderer->SetDrawColor(colors[playerIndex]);
      renderer->DrawRectangle(debugRectPos);
      renderer->RenderTexture(card->Texture(), nullptr, &cardPosition);
    }

    for (const auto& cardWeakPtr : player->CardsOnTable())
    {
      const auto card = cardWeakPtr.lock();
      if (!card)
      {
        std::cerr << "Card is not available; continue" << std::endl;
        continue;
      }

      const auto cardDrawArea =
        card->Entity()->Get<Graphics::Positionable>()->GetAbsoluteDrawArea();
      const auto cardPosition = Utils::DrawAreaToSDLRect(cardDrawArea);

      renderer->RenderTexture(card->Texture(), nullptr, &cardPosition);
    }
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
    application.configComponent->Init(
      ::PlayerPositions,
      { static_cast<uint32_t>(::CardWidth), static_cast<uint32_t>(::CardHeight), Utils::LengthUnits::px },
      ::FirstCardToScreenLeftOffset,
      ::MaxCardsNextToEachOtherWithoutOverlapping);

    // Loading the card banks requires a renderer.
    std::cout << "Loading card banks." << std::endl;
    application.cardBankComponent->LoadAllBanks(::CardBundlesDirectoryPath);

    std::cout << "Loading font." << std::endl;
    auto *font = Utils::LoadFontFromFile(::FontName, 180u);
    if(!font)
      throw Utils::Exception {""};

    std::cout << "Adding font to content storage: " << ::FontName << " " << font << std::endl;
    application.contentStorageComponent->AddFont(::FontName, font);

    std::cout << "Creating state manager with CreatePlayers initial state." << std::endl;
    Bang::StateManager stateManager {
      std::unique_ptr<Bang::State<GameStates>> {new Bang::CreateDeck}};

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
