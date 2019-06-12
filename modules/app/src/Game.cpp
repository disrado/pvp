#include "pch.hpp"

#include "app/Game.hpp"

void Game::Run() const
{
    SDL_Init(SDL_INIT_EVERYTHING);

    auto render{ std::make_shared<Render>(
        std::make_unique<Window>("game", Vector2i{ 200, 200 }, Size{ 720, 480 }),
        Color{ 0, 0, 0, 255 }
    ) };

    const auto entity{ std::make_shared<flm::Entity>() };
    {
        auto transformComponent{ std::make_shared<TransformComponent>() };
        {
            transformComponent->position = Vector2f{ 100, 100 };
            transformComponent->rotation = 45;
            transformComponent->scale = Vector2f{ 1.5, 1.5 };
        }

        auto textureComponent{ std::make_shared<TextureComponent>() };
        {
            textureComponent->texture = std::make_shared<Texture>("picture.png", render);
        }

        entity->AddComponent<TransformComponent>(transformComponent);
        entity->AddComponent<TextureComponent>(textureComponent);
    }

    const auto entity2{ std::make_shared<flm::Entity>() };
    {
        auto transformComponent{ std::make_shared<TransformComponent>() };
        {
            transformComponent->position = Vector2f{ 110, 110 };
            transformComponent->rotation = 64;
            transformComponent->scale = Vector2f{ 1.6, 1.6 };
        }

        auto textureComponent{ std::make_shared<TextureComponent>() };
        {
            textureComponent->texture = std::make_shared<Texture>("picture.png", render);
        }

        entity2->AddComponent<TransformComponent>(transformComponent);
        entity2->AddComponent<TextureComponent>(textureComponent);
    }

    const auto drawSystem{ std::make_shared<DrawSystem>(render) };
    
    auto id{ drawSystem->GetRoot()->AddChild(entity, 1) };
    drawSystem->GetRoot()->AddChild(entity2, 0);

    const auto world{ std::make_unique<flm::World>() };
    {
        world->AddSystem(drawSystem, 1);
    }

    SDL_Event event;

    while (true) {
        float dt{ 0 };
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_MOUSEBUTTONUP) {
                drawSystem->GetRoot()->GetChild(id1)->Apply([] (std::shared_ptr<flm::Entity> entity) {
                    entity->GetComponent<TransformComponent>()->rotation += 5;
                });
            }
            if (event.type == SDL_KEYDOWN) {
                exit(1);
            }
        }

        SDL_RenderClear(render->Get());
        world->Update(dt);
        SDL_RenderPresent(render->Get());
    }
}