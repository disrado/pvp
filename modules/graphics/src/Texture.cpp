#include "pch.hpp"

#include "graphics/Texture.hpp"

#include "graphics/Render.hpp"

Texture::Texture(const std::string& path, std::shared_ptr<Render> render)
{
    if (!(m_texture = IMG_LoadTexture(render->Get(), path.c_str()))) {
        throw std::runtime_error{ "Cannot load texture from "s + path.c_str() };
    }

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_size.width, &m_size.height);
}


Size Texture::GetSize() const {
    return m_size;
}


SDL_Texture* Texture::Get() const
{
    return m_texture;
}
