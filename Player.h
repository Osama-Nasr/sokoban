#pragma once
#include "Item.h"
#include "Bullet.h"
#include "Constants.h"
class Bullet;

class Player :public Item
{
public:
	Player(SDL_Renderer* renderer);
	Player();
	//~Player();

	int directionBullet = 0;
	Bullet* bullet;
	//void bulletMove(Player* item);
	void shoot();
	void bulletMove();

	void move(int x, int y);

	void setPlayerSpeedx(int PSx);
	void setPlayerSpeedy(int PSy);
	void setSpeedY_up(int SY_up);
	void setSpeedY_down(int SY_down);
	void setSpeedX_right(int SX_right);
	void setSpeedX_left(int SX_left);
		
	int getPlayerSpeedx();
	int getPlayerSpeedy();
	int getSpeedY_up();
	int getSpeedY_down();
	int getSpeedX_right();
	int getSpeedX_left();

	void increaseSpeedY_up();
	void increaseSpeedY_down();
	void increaseSpeedX_right();
	void increaseSpeedX_left();	
	
	void decreaseSpeedY_up();
	void decreaseSpeedY_down();
	void decreaseSpeedX_right();
	void decreaseSpeedX_left();

	void setPlayerJustgotHit(bool staute);
	bool getPlayerJustgotHit();
private:
	int playerSpeedx;
	int playerSpeedy;
	int speedY_up;
	int speedY_down;
	int speedX_right;
	int speedX_left;
	bool playerJustgotHit = false;
};

