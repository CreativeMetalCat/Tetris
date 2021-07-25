#include "Game.h"
#include <SDL_image.h>
#include <exception>
#include <Betris/Block.h>
#include <SDL_ttf.h>
#include <Betris/Shapes/Shape4x4.h>
#include <Betris/Shapes/Shape3x3.h>
#include <Betris/Shapes/Shape2x2.h>

Game::Game(int DefaultWindowWidth, int DefaultWindowHeight, glm::vec3 DefaultClearColor):
	defaultWindowHeight(DefaultWindowHeight),defaultClearColor(DefaultClearColor),defaultWindowWidth(DefaultWindowWidth)
{
	if (SDL_Init(SDL_INIT_VIDEO) >= 0) 
	{
		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) )
		{
			throw std::exception(IMG_GetError());
		}
		if (TTF_Init() == -1)
		{
			throw std::exception(TTF_GetError());
		}
		window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, DefaultWindowWidth, DefaultWindowHeight, SDL_WINDOW_SHOWN);
		if (!window)
		{
			throw std::exception(SDL_GetError());
		}
		else 
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (!renderer)
			{
				throw std::exception(SDL_GetError());
			}
			else
			{
				SDL_SetRenderDrawColor(renderer, defaultClearColor.r, defaultClearColor.b, defaultClearColor.g, 255);
			}
		}

	}
	else
	{
		throw std::exception(SDL_GetError());
	}
}

void Game::SpawnNewBlock()
{
	shapes.push_back(new Shape(this,currentShape));
	currentShape = new Shape3x3(this, { 0,0 },1,32);
	currentShape->ShouldMove = true;
}

void Game::LoadAssets()
{
	globalTextureAtlas = LoadTexture("assets/atlas.png");

	currentShape = new Shape3x3(this, { 0,0 }, -1, 32);
	currentShape->ShouldMove = true;

	baseFont = TTF_OpenFont("fonts/8bit_operator/8bitOperatorPlus-Regular.ttf", 25);	
}

SDL_Texture* Game::LoadTexture(std::string texture)
{
	if (SDL_Surface* surface = IMG_Load(texture.c_str()))
	{
		return SDL_CreateTextureFromSurface(renderer, surface);
	}
	return nullptr;
}

void Game::Close()
{
	for (int i = 0; i < shapes.size(); i++)
	{
		shapes[i]->~Shape();
	}

	delete text;

	SDL_DestroyTexture(placeholderTexture);
	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);

	TTF_CloseFont(baseFont);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::Draw()
{
	SDL_RenderClear(renderer);
	currentShape->Draw(renderer);
	 for(int i = 0; i < shapes.size(); i++)
	{
		shapes[i]->Draw(renderer);
	}
	//text->Draw(renderer);

	SDL_RenderPresent(renderer);
}

void Game::Update()
{
	deltaTime = (float)((SDL_GetPerformanceCounter() - lastTime) * 1000 / (double)SDL_GetPerformanceFrequency());
	if (deltaTime < 1)
	{

		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
			{
				needsToClose = true;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_g)
				{
					needsToClose = true;
				}
				if (!isInputDown)
				{
					if (event.key.keysym.sym == SDLK_r && !isInputDown)
					{
						isInputDown = true;
						currentShape->RotateCounterClockwise();
					}
					if (event.key.keysym.sym == SDLK_e)
					{
						isInputDown = true;
						currentShape->RotateClockwise();
					}
					if (event.key.keysym.sym == SDLK_r)
					{
						isInputDown = true;
						currentShape->RotateCounterClockwise();
					}
					if (event.key.keysym.sym == SDLK_e)
					{
						isInputDown = true;
						currentShape->RotateClockwise();
					}

					if (event.key.keysym.sym == SDLK_LEFT)
					{
						isInputDown = true;
						currentShape->MoveSideways(-1);
					}
					if (event.key.keysym.sym == SDLK_RIGHT)
					{
						isInputDown = true;
						currentShape->MoveSideways(1);
					}
				}
			}
			else if (event.type == SDL_KEYUP )
			{
				isInputDown = false;
			}
		}
		currentMovementWaitTime += deltaTime;
		if (currentMovementWaitTime >= movementInterval)
		{
			currentShape->Update(deltaTime);
			//perform collision check(basically check if there is anything 

			currentMovementWaitTime = 0;
		}
	}
	lastTime = SDL_GetPerformanceCounter();
}
