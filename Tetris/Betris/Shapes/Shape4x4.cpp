#include "Shape4x4.h"

Shape4x4::Shape4x4(Game* _game, glm::vec2 _position, int _type, int _blockSize)
	:Shape(_game, _position, _type, _blockSize)
{
	//the only shape that uses matrix this big for calculations is I shape
	blockMatrix =
	{
		{0,0,0,0},
		{1,1,1,1},
		{0,0,0,0},
		{0,0,0,0}
	};

	int y, x, id = 0;
	for (int i = 0; i < 16; i++)
	{
		y = (int)(i / 4);
		x = i - (y * 4);
		if (blockMatrix[y][x])
		{
			blocks[id] = new Block(game, { shapePosition.x + x * blockSize, shapePosition.y + y * blockSize }, { blockSize,blockSize });
			id++;
		}
	}
}

void Shape4x4::RotateCounterClockwise()
{
	glm::mat4 trapMat = glm::transpose(blockMatrix);

	//reverse order of the rows
	for (int i = 0; i < 4; i++)
	{
		blockMatrix[i] = trapMat[3 - i];
	}

	updateBlockRotations();
}

void Shape4x4::RotateClockwise()
{
	glm::mat4 trapMat = glm::transpose(blockMatrix);

	//reverse order of the columns
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			blockMatrix[x][y] = trapMat[x][3 - y];
		}
	}

	updateBlockRotations();
}

void Shape4x4::updateBlockRotations()
{
	int y, x, lastValid = 0;

	for (int i = 0; i < 16; i++)
	{
		y = (int)(i / 4);
		x = i - (y * 4);
		if (blockMatrix[y][x])
		{
			while ((!blocks[lastValid]) && lastValid < 5)
			{
				lastValid++;
			}
			if (lastValid >= 15)
			{
				return;
			}
			blocks[lastValid]->SetPosition({ shapePosition.x + x * blockSize, shapePosition.y + y * blockSize });
			lastValid++;
		}
	}
	
}
