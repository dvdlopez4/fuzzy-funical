#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "TextBox.h";

using namespace std;

int main(int argc, char* argv[])
{
	SDL_Window *window = nullptr;
	SDL_Surface *windowSurface = nullptr;
	SDL_Surface *imageSurface = nullptr;
	SDL_Renderer *renderTarget = nullptr;
	
	int width = 1360,
		height = 720;

	/* Initialize the video */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "Video Initialization Error: " << SDL_GetError() << std::endl;
	else
	{
		/* Sets window with the parameters */
		window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

		if (window == nullptr)
			std::cout << "Window creation error: " << SDL_GetError() << std::endl;
		else
		{
			renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			// Window Created
			SDL_SetRenderDrawColor(renderTarget, 0, 0, 0x55, 0x0);
			if (TTF_Init() < 0)
				printf("Error");
		

			// Test stuff
			TextBox tb(renderTarget, width / 8, height * 3 / 5, 800, 200, "SEASRN__.ttf");
			tb.setColor(20, 150, 130);
			tb.CreateText("in.txt");
			// Test stuff

			while (true)
			{
				SDL_RenderClear(renderTarget);
				tb.Draw();
				SDL_RenderPresent(renderTarget);
			}
		}
	}

	/* Termination clean up */
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();
	TTF_Quit();
	std::cin.get();
	return 0;
}