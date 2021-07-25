#include "TextRender.h"
#include <SDL_ttf.h>

TextRender::TextRender(SDL_Renderer* renderer, std::string text, TTF_Font* font, glm::vec2 position, glm::vec3 color)
{
	if (SDL_Surface* textSurf = TTF_RenderText_Solid(font, text.c_str(), { (Uint8)color.r,(Uint8)color.g,(Uint8)color.b }))
	{
		texture = SDL_CreateTextureFromSurface(renderer, textSurf);
		if (!texture)
		{
			throw std::exception(SDL_GetError());
		}
		SDL_FreeSurface(textSurf);

		resultRect = { (int)position.x,(int)position.y,0,0 };
		SDL_QueryTexture(texture, nullptr, nullptr, &resultRect.w, &resultRect.h);

	}
	else
	{
		throw std::exception(TTF_GetError());
	}
}

void TextRender::Draw(SDL_Renderer* renderer)
{
	if (renderer)
	{
		if (SDL_RenderCopy(renderer, texture, NULL, &resultRect) < 0)
		{
			throw std::exception(SDL_GetError());
		}
	}
}

TextRender::~TextRender()
{
	SDL_DestroyTexture(texture);
}
