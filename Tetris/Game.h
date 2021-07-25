#pragma once
#include <SDL.h>
#include <iostream>
#include <vec3.hpp>
#include <vector>


#include <Betris/Shape.h>
#include <Betris/TextRender.h>


class Block;

//class that handles updates/rendering/init/close
class Game
{
private:
	SDL_Texture* placeholderTexture = nullptr;
	
public:

	Uint64 lastTime = 0;
	float deltaTime = 0;

	bool isInputDown = false;

	int defaultWindowWidth = 1280;
	int  defaultWindowHeight = 720;

	glm::vec3 defaultClearColor;

	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;

	//The window renderer
	SDL_Renderer* renderer = nullptr;

	SDL_Event event;

	bool needsToClose = false;

	//previously spawned shapes
	std::vector<Shape*>shapes = std::vector<Shape*>();

	Shape* currentShape = nullptr;

	SDL_Texture* globalTextureAtlas = nullptr;

	TextRender* text = nullptr;

	TTF_Font* baseFont = nullptr;

	float movementInterval = 100;

	float currentMovementWaitTime = 0;

	int fieldWidth = 10;
	int fieldHeight = 20;

	Game(int DefaultWindowWidth = 420, int DefaultWindowHeight = 720, glm::vec3 defaultClearColor = glm::vec3(0, 0, 0));

	void SpawnNewBlock();

	SDL_Texture* GetAtlasTexture()const { return globalTextureAtlas; }

	bool ShouldQuit()const { return needsToClose; }

	SDL_Texture* LoadTexture(std::string texture);

	glm::vec2 GetFieldSize()const { return { fieldWidth,fieldHeight }; }

	void LoadAssets();

	void Close();

	void Draw();

	void Update();
};

