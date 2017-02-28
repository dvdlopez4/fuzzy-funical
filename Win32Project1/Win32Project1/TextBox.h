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
	TextBox(SDL_Renderer *r, int x, int y, int width, int height)
		:font(nullptr),
		surface(nullptr),
		renderRef(r),
		width(width),
		height(height),
		x(x),
		y(y)
	{
		color = { 255, 255, 255 };
	}

	void loadFile(string s);
	void setFont(string s, int size) { 
		font = TTF_OpenFont(s.c_str(), size); 
		TTF_SizeText(font, " ", &spaceWidth, nullptr);
		skip = TTF_FontLineSkip(font);
		createTextures();
	}

	void Draw();
	void Clear();

private:
	TTF_Font *font;
	vector<SDL_Texture*> textures;
	vector<SDL_Rect> textureRects;
	SDL_Surface *surface;
	SDL_Renderer *renderRef;
	int width;
	int height;
	int x;
	int y;
	int spaceWidth;
	int skip;
	SDL_Color color;
	state State;
	queue<string> Text;

	void createTextures();
};
