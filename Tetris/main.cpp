#include "Game.h"
#include <stdio.h>
#include <exception>

int main(int argc, char* args[])
{
	try 
	{
		Game* game = new Game();
		game->LoadAssets();
		

		
		bool quit = false;

		do
		{
			game->Update();
			game->Draw();
		} while (!game->ShouldQuit());

		game->Close();
	}
	catch (std::exception e)
	{
		printf("%s", e.what());
	}

	return 0;
}