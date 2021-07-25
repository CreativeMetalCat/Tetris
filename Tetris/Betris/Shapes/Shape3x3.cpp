#include "Shape3x3.h"

Shape3x3::Shape3x3(Game* _game, glm::vec2 _position, int _type, int _blockSize)
	:Shape(_game, _position, _type, _blockSize)
{
	blockMatrix =
	{
		{0,1,1},
		{0,1,0},
		{0,1,0},
	};

	int y, x, id = 0;
	for (int i = 0; i < 9; i++)
	{
		y = (int)(i / 3);
		x = i - (y * 3);
		if (blockMatrix[y][x])
		{
			blocks[id] = new Block(game, { shapePosition.x + x * blockSize, shapePosition.y + y * blockSize }, { blockSize,blockSize });
			id++;
		}
	}
}

void Shape3x3::updateBlockRotations()
{
	int y, x, lastValid = 0;

	for (int i = 0; i < 9; i++)
	{
		y = (int)(i / 3);
		x = i - (y * 3);
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

void Shape3x3::RotateCounterClockwise()
{
	glm::mat4 trapMat = glm::transpose(blockMatrix);

	//reverse order of the rows
	for (int i = 0; i < 3; i++)
	{
		blockMatrix[i] = trapMat[2 - i];
	}

	updateBlockRotations();
}

void Shape3x3::RotateClockwise()
{
	glm::mat4 trapMat = glm::transpose(blockMatrix);

	//reverse order of the columns
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			blockMatrix[x][y] = trapMat[x][2 - y];
		}
	}

	updateBlockRotations();
}
