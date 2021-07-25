#include "Shape.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <Game.h>

Shape::Shape(Game* _game, glm::vec2 _position, int _type, int _blockSize)
	:game(_game), shapePosition(_position), type(_type > -1 ? _type : 0 + (rand() % static_cast<int>(2 + 1))), blockSize(_blockSize)
{

}

Shape::Shape(Game* _game, Shape* shape, int _blockSize)
	: game(_game), shapePosition(shape->shapePosition), type(shape->type), blockSize(_blockSize == -1 ? shape->blockSize : _blockSize)
{
	for (int i = 0; i < 4; i++)
	{
		blocks[i] = new Block(game, shape->blocks[i]->GetPosition(), { shape->blockSize,shape->blockSize });
		blocks[i]->Update(0);
	}
}

void Shape::Update(float dt)
{
	if (ShouldMove)
	{
		if (CanMoveDown())
		{
			shapePosition.y += blockSize;
			for (int i = 0; i < 4; i++)
			{
				if (blocks[i])
				{
					blocks[i]->SetPosition(glm::vec2(0, blockSize) + blocks[i]->GetPosition());
				}
			}
		}
		else
		{
			game->SpawnNewBlock();
		}
	}
}

void Shape::Draw(SDL_Renderer* rend)
{
	for (int i = 0; i < 4; i++)
	{
		if (blocks[i])
		{
			blocks[i]->Draw(rend);
		}
	}
}

bool Shape::CanMoveSideways(bool right)
{
	return right ? (game->GetFieldSize().x * blockSize) > (shapePosition.x + blockSize) : (shapePosition.x - blockSize) >= 0;
}

Shape::~Shape()
{
	for (int i = 0; i < 4; i++)
	{
		delete blocks[i];
	}
}

bool Shape::CanMoveDown()
{
	//iterate over everyshape and check if any blocks in that shape overlap
	if (game)
	{
		//first check if any of the blocks are over the edge
		for (int i = 0; i < 4; i++)
		{
			if (blocks[i]->GetPosition().y + blockSize > game->GetFieldSize().y * blockSize)
			{
				return false;
			}
		}

		//not the best method of iteration as this requiers iterating over every block
		//maybegenerating array of objects that just have locations near the shape. However this still implies iterating over every shape
		if (game->shapes.size() > 0)
		{
			for (auto it = game->shapes.begin(); it != game->shapes.end(); ++it)
			{
				for (int i = 0; i < 4; i++)
				{
					for (int u = 0; u < 4; u++)
					{
						if ((*it)->blocks[i]->GetPosition() == (blocks[u]->GetPosition() + glm::vec2(0, blockSize)))
						{
							return false;
						}
					}
				}
			}
		}
		return shapePosition.y < game->GetFieldSize().y* blockSize;
	}
	return false;
}

void Shape::MoveSideways(int value)
{
	if (CanMoveSideways(value > 0))
	{
		shapePosition.x += blockSize * value;

		for (int i = 0; i < 4; i++)
		{
			blocks[i]->SetPosition(blocks[i]->GetPosition() + glm::vec2(value * blockSize, 0));
		}
	}
}

void Shape::MoveDown()
{
}
