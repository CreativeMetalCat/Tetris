#pragma once
#include <SDL.h>
#include <iostream>
#include <vec2.hpp>
#include <vec4.hpp>
#include <SDL_image.h>

class Block;

class Texture
{
private:


protected:
	//Rectangle that represents part of the texture that needs to be drawn
	SDL_Rect frameRect;

	//Rectangle representing postion and scale of the texture
	SDL_Rect resultRect;

	SDL_Texture* texture;

	int width = 0;
	int height = 0;

	glm::vec2 position;

	glm::vec2 size;

	glm::vec4 frame;

	Block* owner = nullptr;
public:
	//Creates texture from given sdl texture
	Texture(SDL_Texture* _texture, Block* owner, glm::vec2 size = glm::vec2(1, 1), glm::vec2 position = glm::vec2(0, 0), glm::vec4 frame = { 0,0,0,0 });

	//creates texture that uses global altas
	//this implies that texture used by this object is named atlas.png
	Texture(Block* owner, glm::vec2 size = glm::vec2(1, 1), glm::vec2 position = glm::vec2(0, 0), glm::vec4 frame = { 0,0,0,0 });

	Texture();

	virtual void Draw(SDL_Renderer* renderer);

	void SetPosition(glm::vec2 pos);

	glm::vec2 GetPosition()const;

	~Texture();
};

