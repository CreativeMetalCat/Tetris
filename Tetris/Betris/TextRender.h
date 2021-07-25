#pragma once
#include "Texture.h"
#include <SDL_ttf.h>
#include <vec2.hpp>
#include <vec3.hpp>

class TextRender :
    public Texture
{
protected:
    glm::vec3 color = { 0,0,0 };
public:
    TextRender(SDL_Renderer*renderer,std::string text, TTF_Font* font, glm::vec2 position = glm::vec2(0, 0), glm::vec3 color = { 0,0,0 });

    virtual void Draw(SDL_Renderer* renderer);

    ~TextRender();
};

