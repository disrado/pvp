#include "pch.hpp"

#include <graphics/DrawSystem.hpp>

#include <graphics/Components.hpp>
#include <graphics/Render.hpp>

DrawSystem::DrawSystem(std::shared_ptr<Render> render)
    : m_root{ std::make_shared<flm::Node<flm::Entity>>() }
    , m_render{ render }
{
}


std::shared_ptr<flm::Node<flm::Entity>> DrawSystem::Root()
{
    return m_root;
}


void DrawSystem::Update(float dt)
{
    m_root->Apply([render = m_render, dt] (std::shared_ptr<flm::Entity> entity) {
        if (!entity) {
            return;
        }

        const auto transform{ entity->GetComponent<TransformComponent>() };
        const auto texture{ entity->GetComponent<TextureComponent>() };

        if (!texture || !transform) {
            return;
        }

        SDL_Rect rect;
        rect.w = texture->texture->GetSize().width * transform->scale.x;
        rect.h = texture->texture->GetSize().height * transform->scale.y;
        rect.x = transform->position.x;
        rect.y = transform->position.y;

        SDL_RenderCopyEx(render->Get(), texture->texture->Get(), nullptr, &rect,
            transform->rotation, nullptr, SDL_FLIP_NONE
        );
    });
}