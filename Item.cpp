#include "Item.h"

void ItemInit() 
{
	SDL_Init(SDL_INIT_EVERYTHING);
	//IMG_Init(IMG_INIT_BMP);
}

void ItemQuit() 
{
	SDL_Quit;
}

void Item::setRenderer(SDL_Renderer *dest)
{
	ren = dest;
}

Item::Item()
{
	pos.x = 30;
	pos.y = 60;
	image = NULL;
	pos.w = 50;
	pos.h = 50;
}

Item::~Item()
{
	if (image != NULL) {
		SDL_DestroyTexture(image);	
		image = NULL;
	}
}

bool Item::loadImage(char filename[])
{
	if (image != NULL) 
	{
		SDL_DestroyTexture(image);
		image = NULL;
	}
	SDL_Surface* temp = SDL_LoadBMP(filename);
	if (temp != NULL)
	{
		image = SDL_CreateTextureFromSurface(ren, temp);
		SDL_FreeSurface(temp);
		if (image != NULL)
			return true;
	}
	return false;
}

void Item::setSize(int w, int h)
{
	pos.w = w;
	pos.h = h;
}

void Item::setPos(int x, int y)
{
	if (x >= 0 && y>=0) {
		pos.x = x;
		pos.y = y;
	}
}

void Item::draw()
{
	if (image != NULL)
	{
		SDL_RenderCopy(ren, image, NULL, &pos);
	}
}

SDL_Rect* Item::getPos()
{
	return &pos;
}

