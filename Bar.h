#pragma once
#include "Item.h"

class Bar: public Item {
public:
	Bar(SDL_Renderer* renderer);
	Bar(SDL_Renderer* renderer, SDL_Rect p);
	Bar();
};