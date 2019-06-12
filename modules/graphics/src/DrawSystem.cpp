#include "pch.hpp"

#include <graphics/DrawSystem.hpp>

#include <graphics/Components.hpp>
#include <graphics/Render.hpp>

#include <iostream>

DrawSystem::Node::~Node()
{
    if (auto parent = m_parent.lock()) {
        parent->RemoveChild(id);
    }
}


bool DrawSystem::Node::operator<(const DrawSystem::Node& other) const
{
    return drawOrder < other.drawOrder;
}


flm::Id DrawSystem::Node::AddChild(std::shared_ptr<flm::Entity> entity, int64_t drawOrder)
{
    const auto node{ std::make_shared<DrawSystem::Node>() };
    node->entity = entity;
    node->drawOrder = drawOrder;
    node->m_parent = shared_from_this();
    
    m_children.push_back(node);

    std::sort(std::begin(m_children), std::end(m_children), [] (auto rhs, auto lhs) {
        return *rhs < *lhs;
    });

    return node->id;
}


std::shared_ptr<DrawSystem::Node> DrawSystem::Node::GetChild(flm::Id id)
{
    for (auto child : m_children) {
        if (child->id == id) {
            return child;
        }
    }

    return nullptr;
}


bool DrawSystem::Node::RemoveChild(flm::Id id)
{
    const auto it{ std::find_if(std::begin(m_children), std::end(m_children),
        [id] (const auto& child) { return child->entity->id == id; })
    };

    if (it != std::end(m_children)) {
        m_children.erase(it);
        return true;
    }

    return false;
}


void DrawSystem::Node::Apply(std::function<void(std::shared_ptr<flm::Entity>)> function)
{
    function(entity);
    
    for(const auto& child : m_children) {
        child->Apply(function);
    }
}


void DrawSystem::Node::Draw(std::shared_ptr<Render> render, const float dt)
{
    for (const auto& child : m_children) {
        child->Draw(render, dt);
    }

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

    SDL_RenderCopyEx(render->Get(), texture->texture->Get(), nullptr, &rect, transform->rotation, 
        nullptr, SDL_FLIP_NONE
    );
}


DrawSystem::DrawSystem(std::shared_ptr<Render> render)
    : m_root{ std::make_shared<DrawSystem::Node>() }
    , m_render{ render }
{
}


std::shared_ptr<DrawSystem::Node> DrawSystem::GetRoot()
{
    return m_root;
}


void DrawSystem::Update(float dt)
{
    m_root->Draw(m_render, dt);
}