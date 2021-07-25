#pragma once
#include "Texture.h"

class Game;

class Block
{
protected:
	Texture* texture = nullptr;

	glm::vec2 position;

	Game* game = nullptr;
public:
	Game* GetGame() { return game; }

	Block(Game* game, glm::vec2 _position, glm::vec2 size = { 64,64 });

	void SetPosition(glm::vec2 pos);

	glm::vec2 GetPosition()const { return position; }

	void Update(float deltaTime);

	void Draw(SDL_Renderer* renderer);

	~Block();
};

