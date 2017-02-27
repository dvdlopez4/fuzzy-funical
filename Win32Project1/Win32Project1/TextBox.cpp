#include "TextBox.h"


void TextBox::loadFile(string s)
{
	ifstream in(s.c_str());
	string word;
	while (in >> word)
		text.push_back(word);
	in.close();
}

void TextBox::createTextures()
{
	surface = TTF_RenderText_Solid(font, text[0].c_str(), color);
	string line;
	SDL_Rect rect;
	int currentWidth = 0;
	int numOfLines = 0;

	for (int i = 0; i < text.size(); ++i)
	{
		TTF_SizeText(font, line.c_str(), &currentWidth, nullptr);
		if (currentWidth <= (width - x))
			line += text[i] + " ";
		else
		{
			--i;
			string::size_type pos;
			pos = line.find_last_of( ' ' );
			if (string::npos != pos) line.erase(pos, line.length());
			surface = TTF_RenderText_Solid(font, line.c_str(), color);
			textures.push_back(SDL_CreateTextureFromSurface(renderRef, surface));

			rect.x = x;
			rect.y = y + skip * numOfLines++;
			SDL_QueryTexture(textures.back(), nullptr, nullptr, &rect.w, &rect.h);
			textureRects.push_back(rect);
			line.clear();
		}
	}
	surface = TTF_RenderText_Solid(font, line.c_str(), color);
	textures.push_back(SDL_CreateTextureFromSurface(renderRef, surface));

	rect.x = x;
	rect.y = y + skip * numOfLines++;
	SDL_QueryTexture(textures.back(), nullptr, nullptr, &rect.w, &rect.h);
	textureRects.push_back(rect);

	text.clear();
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