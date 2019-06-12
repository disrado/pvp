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
    std::shared_ptr<Texture> texture = nullptr;
};
