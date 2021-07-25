#include "Block.h"
#include <Game.h>

Block::Block(Game* _game, glm::vec2 _position, glm::vec2 size)
	:position(_position),game(_game)
{
	texture = new Texture(this, size, { 0,0 }, { 0,0,16,16 });
}

void Block::SetPosition(glm::vec2 pos)
{
	position = pos;
	texture->SetPosition(pos);
}

void Block::Update(float deltaTime)
{
	texture->SetPosition(position);
}

void Block::Draw(SDL_Renderer* renderer)
{
	texture->Draw(renderer);
}

Block::~Block()
{
	delete texture;
}
