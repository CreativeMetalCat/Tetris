#pragma once
#include <Betris/Shape.h>
#include <glm/mat3x3.hpp>

class Shape3x3 : public Shape
{
protected:
	glm::mat3 blockMatrix;


public:
	Shape3x3(Game* _game, glm::vec2 _position = { 0,0 }, int _type = -1, int _blockSize = 64);

	// Inherited via Shape
	virtual void updateBlockRotations() override;
	virtual void RotateCounterClockwise() override;
	virtual void RotateClockwise() override;
};

