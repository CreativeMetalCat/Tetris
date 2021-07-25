#include "Shape2x2.h"

void Shape2x2::updateBlockRotations()
{
	blocks[0]->SetPosition({ shapePosition.x,shapePosition.y });
	blocks[1]->SetPosition({ shapePosition.x + blockSize,shapePosition.y });
	blocks[2]->SetPosition({ shapePosition.x,shapePosition.y + blockSize });
	blocks[3]->SetPosition({ shapePosition.x + blockSize,shapePosition.y + blockSize });
}

void Shape2x2::RotateCounterClockwise()
{
}

void Shape2x2::RotateClockwise()
{
}

Shape2x2::Shape2x2(Game* _game, glm::vec2 _position , int _type , int _blockSize)
	:Shape(_game,_position,_type,_blockSize)
{
	blocks[0] = new Block(_game, { shapePosition.x,shapePosition.y }, { blockSize,blockSize });
	blocks[1] = new Block(_game, { shapePosition.x + blockSize,shapePosition.y }, { blockSize,blockSize });
	blocks[2] = new Block(_game, { shapePosition.x,shapePosition.y + blockSize }, { blockSize,blockSize });
	blocks[3] = new Block(_game, { shapePosition.x + blockSize,shapePosition.y + blockSize }, { blockSize,blockSize });
}
