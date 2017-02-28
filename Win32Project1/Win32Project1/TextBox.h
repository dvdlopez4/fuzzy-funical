#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum state { BEGIN, CREATE_LINE, CREATE_TEXTURE, END };

class TextBox
{
public:

	TextBox(SDL_Renderer *r, int x, int y, int width, int height, string font)
		:font(nullptr),
		surface(nullptr),
		renderRef(r)
	{
		boxRect = { x, y, width, height };
		color = { 255, 255, 255 };
		this->font = TTF_OpenFont(font.c_str(), 20);
		skip = TTF_FontLineSkip(this->font);
	}
	void CreateText(string inputFile);
	void setFont(string s, int size);
	void setColor(Uint8 r, Uint8 g, Uint8 b) { color = { r, g, b }; }
	void Draw();
	void Clear();

private:
	TTF_Font *font;
	vector<SDL_Texture*> textures;
	vector<SDL_Rect> textureRects;
	SDL_Texture *box_Texture;
	SDL_Surface *surface;
	SDL_Renderer *renderRef;
	SDL_Rect boxRect;
	int skip;
	SDL_Color color;
	state State;
	queue<string> Text;

	void createTextures();
};
