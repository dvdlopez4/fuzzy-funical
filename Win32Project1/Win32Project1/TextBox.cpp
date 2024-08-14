#include "TextBox.h"


void TextBox::CreateText(string inputFile)
{
	ifstream in(inputFile.c_str());
	string word;
	while (in >> word)
		Text.push(word);
	in.close();
	createTextures();
}


void TextBox::createTextures()
{
	string line;
	SDL_Rect rect;
	int numOfLines = 0;
	int currentWidth = 0;
	State = BEGIN;

	/* Underlying box slightly larger than text area */
	rect = boxRect;
	rect.w += 10;
	rect.h += 10;
	rect.x -= 10;
	rect.y -= 10;

	/* Create underlying box for text box */
	surface = SDL_CreateRGBSurface(0, rect.w, rect.h, 32, 0, 0, 0, 0);
	SDL_FillRect(surface, nullptr, 0x004444);
	textures.push_back(SDL_CreateTextureFromSurface(renderRef, surface));
	textureRects.push_back(rect);
	rect = { 0, 0, 0, 0 };

	while (State != END)
	{
		switch (State)
		{
		case BEGIN:
			/* Ensure there is text to be rendered*/
			if (!Text.empty())
				State = CREATE_LINE;
			else
				State = END;
			break;
		case CREATE_LINE:

			/* Check if width is less than text box width */
			TTF_SizeText(font, (line + Text.front() + " ").c_str(), &currentWidth, nullptr);
			if (currentWidth < boxRect.w)
			{
				/* Remove word from Text vector (no need to hold onto to that info anymore, currently) */
				line += Text.front() + " ";
				Text.pop();

				/* Once all the words have been used create texture */
				if (Text.empty()) 
				{
					State = CREATE_TEXTURE;
					break;
				}
			}
			else
				State = CREATE_TEXTURE;
			break;
		case CREATE_TEXTURE:
			/* Texture creation */
			surface = TTF_RenderText_Solid(font, line.c_str(), color);
			textures.push_back(SDL_CreateTextureFromSurface(renderRef, surface));

			/* Texture placement */
			rect.x = boxRect.x;
			rect.y = boxRect.y + skip * numOfLines++; // numOfLines increments for each new line
			SDL_QueryTexture(textures.back(), nullptr, nullptr, &rect.w, &rect.h);
			textureRects.push_back(rect);

			/* Clearing line for future use */
			line.clear();
			if (Text.empty())
			{
				State = END;
				SDL_FreeSurface(surface);
			}
			else
				State = CREATE_LINE;
			break;
		default:
			break;
		}
	}
}

void TextBox::Draw()
{
	for (size_t i = 0; i < textures.size(); ++i)
		SDL_RenderCopy(renderRef, textures[i], nullptr, &textureRects[i]);
}

void TextBox::setFont(string s, int size)
{
	font = TTF_OpenFont(s.c_str(), size);
	skip = TTF_FontLineSkip(font);
	TTF_CloseFont(font);
}

void TextBox::Clear()
{
	for (size_t i = 0; i < textures.size(); ++i)
		SDL_DestroyTexture(textures[i]);

	textures.clear();
	textureRects.clear();
}