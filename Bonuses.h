#pragma once
#include "Item.h"
#include "Player.h"

class Player;


class Bonuses :public Item {
public:
	Bonuses(SDL_Renderer* renderer);
	bool getLife();
	void setLife(bool staute);
	bool getHaveBeenTakenBefore();
	void setHaveBeenTakenBefore(bool staute);
	void checkCollisionWithPlayer(Player *player);

private:
	bool life = false;	//false mean dead 
	bool haveBeenTakenBefore = false;
};