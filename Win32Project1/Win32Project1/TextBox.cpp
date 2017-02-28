#include "TextBox.h"


void TextBox::loadFile(string s)
{
	ifstream in(s.c_str());
	string word;
	while (in >> word)
		Text.push(word);
	in.close();
}

void TextBox::createTextures()
{
	string line;
	SDL_Rect rect;
	int numOfLines = 0;
	int currentWidth = 0;
	State = BEGIN;

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
			if (currentWidth < (width - x))
			{
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
			rect.x = x;
			rect.y = y + skip * numOfLines++;
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
	for (int i = 0; i < textures.size(); ++i)
		SDL_RenderCopy(renderRef, textures[i], nullptr, &textureRects[i]);
}

void TextBox::Clear()
{
	for (int i = 0; i < textures.size(); ++i)
		SDL_DestroyTexture(textures[i]);

	textures.clear();
	textureRects.clear();
}