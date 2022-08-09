#include "Bonuses.h"
#include <stdlib.h>
#include <time.h>


Bonuses::Bonuses(SDL_Renderer* renderer)
{
	srand(time(0));
	setRenderer(renderer);
	loadImage("./heart.bmp");
	setPos(rand() % 640, rand() % 480);
	setSize(20,20);
}

bool Bonuses::getLife()
{
	return life;
}

void Bonuses::setLife(bool staute)
{
	life = staute;
}

bool Bonuses::getHaveBeenTakenBefore()
{
	return haveBeenTakenBefore;
}

void Bonuses::setHaveBeenTakenBefore(bool staute)
{
	haveBeenTakenBefore = staute;
}

void Bonuses::checkCollisionWithPlayer(Player *player)
{
	if (pos.x + 15 >= player->getPos()->x &&
		pos.x + 15 <= player->getPos()->x + player->getPos()->w &&
		pos.y + 15 >= player->getPos()->y &&
		pos.y + 15 <= player->getPos()->y + player->getPos()->h && getLife() == true)
	{
		setLife(false);
		player->blood += 0.2f;
		setHaveBeenTakenBefore(true);
	}
}
