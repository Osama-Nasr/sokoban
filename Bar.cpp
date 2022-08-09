#include "Bar.h"

Bar::Bar(SDL_Renderer* renderer)
{
	setRenderer(renderer);
	loadImage("./bar.bmp");
	setPos(0,450);
}

Bar::Bar(SDL_Renderer* renderer, SDL_Rect p)
{
	setRenderer(renderer);
	loadImage("./bar.bmp");
	setPos(p.x + 15,p.y - 20);
	setSize(20,10);
}

Bar::Bar()
{
}
