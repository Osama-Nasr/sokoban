#pragma once
#include<stdio.h>
#include<string.h>
#include"Player.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

class Draw {
private:
	SDL_Surface* charset;
public:
	Draw();
	~Draw();

	char text[128];
	void TextStartingMenu(SDL_Surface* screen, SDL_Surface* eti);
	void TextOptions(SDL_Surface *screen, SDL_Surface* eti, double& enemyShootEverySEC, int activeOption, Player player, int level);
	void TextGame(SDL_Surface* screen, double worldTime, double fps, int numberOfHits, int numberOfgettingShooted, int points);
	void TextContinueMenu(SDL_Surface* screen, SDL_Surface* eti, int points);

	void DrawString(SDL_Surface* screen, int x, int y, const char* text);
	void DrawSurface(SDL_Surface* screen, SDL_Surface* sprite, int x, int y);
	void DrawPixel(SDL_Surface* surface, int x, int y, Uint32 color);
	void DrawLine(SDL_Surface* screen, int x, int y, int l, int dx, int dy, Uint32 color);
	void DrawRectangle(SDL_Surface* screen, int x, int y, int l, int k,
		Uint32 outlineColor, Uint32 fillColor);

};