#pragma once

struct SDL_Texture;

class Render;

class Texture
{
public:
    Texture(const std::string& path, std::shared_ptr<Render> render);
    
    Size GetSize() const;
    SDL_Texture* Get() const;

private:
    SDL_Texture* m_texture = nullptr;
    Size m_size = { 0, 0 };
};
