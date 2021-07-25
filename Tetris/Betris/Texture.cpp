#include "Texture.h"
#include "Block.h"
#include <Game.h>

void Texture::Draw(SDL_Renderer* renderer)
{
	if (renderer)
	{
		if (SDL_RenderCopy(renderer, texture, &frameRect, &resultRect) < 0)
		{
			throw std::exception(SDL_GetError());
		}
	}
}

void Texture::SetPosition(glm::vec2 pos)
{
	position = pos;
	resultRect.x = pos.x;
	resultRect.y = pos.y;
}

Texture::Texture(SDL_Texture* _texture, Block* owner, glm::vec2 _size, glm::vec2 _position, glm::vec4 _frame)
	:texture(_texture), position(_position),size(size),frame(frame)
{
	if (texture)
	{
		if (_frame == glm::vec4(0, 0, 0, 0))
		{
			frameRect = { 0,0, 0, 0 };

			SDL_QueryTexture(texture, NULL, NULL, &frameRect.w, &frameRect.h);

			_frame = glm::vec4(0, 0, frameRect.w, frameRect.h);
		}
		else
		{
			frameRect = { (int)_frame.x,(int)_frame.y,(int)_frame.z,(int)_frame.w };
		}

		resultRect = { (int)position.x,(int)position.y,(int)(_size.x > 0 ? _size.x : frameRect.w),(int)(_size.y > 0 ? _size.y : frameRect.h) };
	}
	else
	{
		throw std::exception("Invalid raw texture was passed into texture object");
	}
}

Texture::Texture(Block* owner, glm::vec2 _size, glm::vec2 _position, glm::vec4 _frame)
	:texture(owner->GetGame()->GetAtlasTexture()), position(_position), size(size), frame(frame)
{
	if (texture)
	{
		if (_frame == glm::vec4(0, 0, 0, 0))
		{
			frameRect = { 0,0, 0, 0 };

			SDL_QueryTexture(texture, NULL, NULL, &frameRect.w, &frameRect.h);

			_frame = glm::vec4(0, 0, frameRect.w, frameRect.h);
		}
		else
		{
			frameRect = { (int)_frame.x,(int)_frame.y,(int)_frame.z,(int)_frame.w };
		}

		resultRect = { (int)position.x,(int)position.y,(int)(_size.x > 0 ? _size.x : frameRect.w),(int)(_size.y > 0 ? _size.y : frameRect.h) };
	}
	else
	{
		throw std::exception("Invalid raw texture was passed into texture object");
	}
}

Texture::Texture()
{
}

glm::vec2 Texture::GetPosition() const
{
	return position;
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}
