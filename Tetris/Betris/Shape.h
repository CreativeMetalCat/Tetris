#pragma once
#include <Betris/Block.h>
#include <mat4x4.hpp>

class Game;

class Shape
{
protected:

	Game* game = nullptr;

	//this updates with same speed as blocks and is used when updating blocks after rotation
	glm::vec2 shapePosition;

	virtual void updateBlockRotations() {}
public:

	Game* GetGame() { return game; }

	bool ShouldMove = false;

	//type is a value from 0 to 2 that basically represents what shape it is
	int type = 0;

	int blockSize = 64;

	//all shapes used here are have block count of 4 for simplicity
	Block* blocks[4];

	Shape(Game* game, glm::vec2 _position = { 0,0 }, int _type = -1,int _blockSize = 64);

	Shape(Game* _game, Shape* shape, int _blockSize = -1);

	void Update(float dt);

	void Draw(SDL_Renderer* rend);

	virtual bool CanMoveSideways(bool right = true);

	virtual bool CanMoveDown();

	virtual void RotateCounterClockwise() {}

	virtual void RotateClockwise() {}

	//Move to the left if -1 or right if 1
	virtual void MoveSideways(int value);

	virtual void MoveDown();

	~Shape();
};

