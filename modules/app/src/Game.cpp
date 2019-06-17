#include "pch.hpp"

#include "app/Game.hpp"

using std::make_shared;

void Game::Run() const
{
    SDL_Init(SDL_INIT_EVERYTHING);

    auto render{ make_shared<Render>(
        std::make_unique<Window>("game", Vector2i{ 200, 200 }, Size{ 1920, 1080 }),
        Color{ 0, 0, 0, 255 }
    ) };

    auto world{ std::make_unique<flm::World>() };

    auto backgroundLayer{ make_shared<flm::Node<flm::Entity>>() };
    {
        auto backgroundTransform{ make_shared<TransformComponent>() };

        auto sky{ world->CreateEntity() };
        {
            sky->AddComponent<TransformComponent>(make_shared<TransformComponent>());
            sky->AddComponent<TextureComponent>(make_shared<TextureComponent>("Sky.png", render));
        }
        auto bgDecor{ world->CreateEntity() };
        {
            bgDecor->AddComponent<TransformComponent>(make_shared<TransformComponent>());
            bgDecor->AddComponent<TextureComponent>(make_shared<TextureComponent>("BG_Decor.png", render));
        }
        auto midDecor{ world->CreateEntity() };
        {
            midDecor->AddComponent<TransformComponent>(make_shared<TransformComponent>());
            midDecor->AddComponent<TextureComponent>(make_shared<TextureComponent>("Middle_Decor.png", render));
        }
        auto foreground{ world->CreateEntity() };
        {
            foreground->AddComponent<TransformComponent>(make_shared<TransformComponent>());
            foreground->AddComponent<TextureComponent>(make_shared<TextureComponent>("Foreground.png", render));
        }
        auto ground{ world->CreateEntity() };
        {
            ground->AddComponent<TransformComponent>(make_shared<TransformComponent>());
            ground->AddComponent<TextureComponent>(make_shared<TextureComponent>("Ground.png", render));
        }

        backgroundLayer->AddChild(sky, 5);
        backgroundLayer->AddChild(bgDecor, 4);
        backgroundLayer->AddChild(midDecor, 3);
        backgroundLayer->AddChild(foreground, 3);
        backgroundLayer->AddChild(ground, 3);
    }

    auto gameplayLayer{ make_shared<flm::Node<flm::Entity>>() };
    {
        auto character{ world->CreateEntity() };
        {
            auto transform{ make_shared<TransformComponent>() };
            {
                transform->scale = Vector2f{ 0.5, 0.5 };
                transform->position = Vector2f{ 10, 400 };
            }
            character->AddComponent<TransformComponent>(transform);
            character->AddComponent<TextureComponent>(make_shared<TextureComponent>("1_IDLE_000.png", render));

        }

        gameplayLayer->AddChild(character, 0);
    }

    auto drawSystem{ make_shared<DrawSystem>(render) };
    {
        drawSystem->Root()->AddChild(backgroundLayer);
        drawSystem->Root()->AddChild(gameplayLayer);
    }
    world->AddSystem(drawSystem, 1);

    SDL_Event event;

    while (true) {
        float dt{ 0 };
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONUP) {
                exit(1);
            }
        }

        SDL_RenderClear(render->Get());
        world->Update(dt);
        SDL_RenderPresent(render->Get());
    }
}