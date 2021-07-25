#pragma once
#include <Betris/Shape.h>

//cube. this is ment for cube and as such does not even have rotation functions
class Shape2x2 : public Shape
{
public:
	Shape2x2(Game* _game, glm::vec2 _position = { 0,0 }, int _type = -1, int _blockSize = 64);

	// Inherited via Shape
	virtual void updateBlockRotations() override;
	virtual void RotateCounterClockwise() override;
	virtual void RotateClockwise() override;
};

