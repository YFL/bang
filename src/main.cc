#include <BangLib/Application.h>
#include <BangLib/CreatePlayers.h>
#include <BangLib/GameState.h>
#include <BangLib/GameStates.h>
#include <BangLib/StateManager.h>
#include <BangLib/TextUtils.h>

#include <iostream>

namespace
{

constexpr auto WindowWidth = 1024u;
constexpr auto WindowHeight = 720u;

constexpr auto CardsPerWindowHorizontal = 4;
constexpr auto CardWidth = WindowWidth / CardsPerWindowHorizontal;
constexpr auto CardsPerWindowVertical = 4;
constexpr auto CardHeight = WindowHeight / CardsPerWindowVertical;

const std::vector<SDL_Rect> PlayerPositions {
  {0, CardHeight},
  {WindowWidth - CardWidth, CardHeight}
};

constexpr auto CardBundlesDirectoryPath = "./cardBundles";
  
} // namespace 

auto DrawGameState(const std::unique_ptr<Bang::Renderer> &renderer, const Bang::GameState &gameState) -> void
{
  for(auto playerIndex = 0u; playerIndex < gameState.players.size(); ++playerIndex)
  {
    std::cerr << "Drawing player #" << playerIndex << " state." << std::endl;
    const auto &player = gameState.players[playerIndex];
    if(!player)
      throw Bang::Exception {"Null player found when drawing the game state." };
    
    const auto &cardsInHand = player->CardsInHand();
    const auto playerTopLeft = ::PlayerPositions[playerIndex];
    std::cerr << "Player #" << playerIndex << " position: " << playerTopLeft.x << ", " << playerTopLeft.y << std::endl;
    for(auto cardIndex = 0u; cardIndex < cardsInHand.size(); ++cardIndex)
    {
      std::cerr << "Drawing card #" << cardIndex <<" state." << std::endl;
      const SDL_Rect cardPosition {
        playerTopLeft.x,
        playerTopLeft.y + static_cast<int32_t>(cardIndex * ::CardHeight),
        ::CardWidth,
        ::CardHeight
      };

      std::cerr << "Card #" << cardIndex << " position: " << cardPosition.x << ", " << cardPosition.y << ", " << cardPosition.w << ", " << cardPosition.h << std::endl;
      renderer->RenderTexture(cardsInHand[cardIndex]->Texture(), nullptr, &cardPosition);
      std::cerr << " Card #" << cardIndex << " drawn." << std::endl;
    }

    std::cerr << "Drawing player #" << playerIndex << "'s character." << std::endl;
    auto *character = player->Character();
    if(!character)
    {
      std::cerr << "No character available." << std::endl;
      return;
    }

    const SDL_Rect characterPosition {
      playerTopLeft.x,
      playerTopLeft.y + static_cast<int32_t>(cardsInHand.size() * ::CardHeight),
      ::CardWidth,
      ::CardHeight
    };
    
    std::cerr << "Character position: " << characterPosition.x << ", " << characterPosition.y << ", " << characterPosition.w << ", " << characterPosition.h << std::endl;
    renderer->RenderTexture(character->Texture(), nullptr, &characterPosition);
    std::cerr << "Drawing player #" << playerIndex << "'s character finished." << std::endl;
  }
}

auto main() -> int
{
  try
  {
    auto &application = Bang::Application::Get();
    auto &window = application.renderingComponent->window;
    std::cout << "Creating window." << std::endl;
    window = std::unique_ptr<Bang::Window> {new Bang::Window {::WindowWidth, ::WindowHeight, "Bang"}};
    auto &renderer = window->renderer;

    // Loading the card banks requires a renderer.
    std::cout << "Loading card banks." << std::endl;
    application.cardBankComponent->LoadAllBanks(::CardBundlesDirectoryPath);

    const auto fontName = "./font.ttf";
    std::cout << "Loading font." << std::endl;
    auto *font = Bang::LoadFontFromFile(fontName, 180u);
    if(!font)
      throw Bang::Exception {""};

    std::cout << "Adding font to content storage: " << fontName << " " << font << std::endl;
    application.contentStorageComponent->AddFont(fontName, font);
    
    std::cerr << "Creating state manager with CreatePlayers initial state." << std::endl;
    Bang::StateManager<Bang::State<GameStates>> stateManager {std::unique_ptr<Bang::State<GameStates>> {new Bang::CreatePlayers}};
    Bang::GameState gameState;

    SDL_Event event;
    while(event.type != SDL_QUIT)
    {
      std::cerr << "Polling events." << std::endl;
      if(SDL_PollEvent(&event))
      {
        if(event.type == SDL_QUIT)
          break;
        else if(event.type == SDL_KEYDOWN)
        {
          if(event.key.keysym.sym == SDLK_ESCAPE)
          break;
        }
      }

      std::cerr << "Event polling finished." << std::endl;
      std::cerr << "Updating the state manager." << std::endl;
      stateManager.Update(gameState);
      std::cerr << "State manager updated." << std::endl;

      std::cerr << "Clearing renderer." << std::endl;
      renderer->ClearRenderer(SDL_Color {255, 255, 255, 255});
      std::cerr << "Renderer cleared." << std::endl;

      std::cerr << "Drawing the game state." << std::endl;
      DrawGameState(renderer, gameState);
      std::cerr << "Drawing finished" << std::endl;

      std::cerr << "Presenting the rendererd frame." << std::endl;
      renderer->RenderPresent();
      std::cerr << "Presenting finished." << std::endl;
    }
  }
  catch(const Bang::Exception &e)
  {
    std::cerr << e.Message() << std::endl;
    return -1;
  }

  return 0;
}