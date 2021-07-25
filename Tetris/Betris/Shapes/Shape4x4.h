#pragma once
#include <Betris/Shape.h>
#include <glm/mat4x4.hpp>

class Shape4x4 : public Shape
{
protected:

	//matrix used to simplify rotation of the blocks
	glm::mat4 blockMatrix;
public:
	Shape4x4(Game* _game, glm::vec2 _position = { 0,0 }, int _type = -1, int _blockSize = 64);

	// Inherited via Shape
	virtual void RotateCounterClockwise() override;
	virtual void RotateClockwise() override;

	// Inherited via Shape
	virtual void updateBlockRotations() override;
};

