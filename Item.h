#pragma once
#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>


extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

void ItemInit();
void ItemQuit();

class Item
{
public:
	Item();
	~Item();
	//virtual Item();
	void setRenderer(SDL_Renderer *renderer);
	bool loadImage(char filename[]);
	void setSize(int w, int h);
	void setPos(int x, int y); 
	//void move(int x, int y);
	void draw();
	//void draw(double angle);
	SDL_Rect* getPos();
	bool isEnemy = false;
	bool isPlayer = false;
	float blood = 0.0f;

protected:
	SDL_Texture* image;
	SDL_Rect pos;
	SDL_Renderer* ren;

private:
	
}; 


	