#pragma once

#include <ecs/Entity.hpp>
#include <graphics/Texture.hpp>

struct TransformComponent
{
    Vector2f position = { 0, 0 };
    Vector2f scale = { 1, 1 };
    float rotation = 0;
};


struct TextureComponent
{
    TextureComponent() = default;

    TextureComponent(const std::string& path, std::shared_ptr<Render> render)
    {
        texture = std::make_shared<Texture>(path, render);
    }

    std::shared_ptr<Texture> texture = nullptr;
};
