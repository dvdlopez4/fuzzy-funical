#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

int main(int argc, char* argv[])
{
	SDL_Window *window = nullptr;
	SDL_Surface *windowSurface = nullptr;
	SDL_Surface *imageSurface = nullptr;
	SDL_Renderer *renderTarget = nullptr;

	/* Initialize the video */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "Video Initialization Error: " << SDL_GetError() << std::endl;
	else
	{
		/* Sets window with the parameters */
		window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
		
		if (window == nullptr)
			std::cout << "Window creation error: " << SDL_GetError() << std::endl;
		else
		{
			renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			// Window Created
			SDL_SetRenderDrawColor(renderTarget, 0, 0, 0x55, 0x0);
			
			SDL_Color color;
			TTF_Font *font = TTF_OpenFont("SEASRN__.ttf", 20);
			SDL_Rect textRect;
			SDL_Surface *textSurface = nullptr;
			SDL_Texture *textTexture = nullptr;

			color = { 255, 255, 255 };
			textRect.x = (int)640 / 2;
			textRect.y = (int)480 / 2;

			textSurface = TTF_RenderText_Solid(font, "Karen Yulissa Beza Lopez", color);
			textTexture = SDL_CreateTextureFromSurface(renderTarget, textSurface);

			if (textTexture == nullptr)
				printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());

			SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);
			SDL_FreeSurface(textSurface);
			textSurface = nullptr;


			SDL_RenderClear(renderTarget);
			SDL_RenderCopy(renderTarget, textTexture, nullptr, &textRect);
			SDL_RenderPresent(renderTarget);
			SDL_Delay(5000); // The window will display for 5 seconds

		}
	}

	/* Termination clean up */
	SDL_DestroyWindow(window);
	window = nullptr;
	SDL_Quit();

	std::cin.get();
	return 0;
}