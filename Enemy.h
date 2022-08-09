#pragma once
#include<stdio.h>
#include "Item.h"
#include "Bullet.h"
#include "Bar.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

class Enemy : public Item
{
public:
	Enemy(SDL_Renderer* renderer);
	Enemy();
	//~Enemy();
	int directionBullet = 0;
	Bullet** bullet;
	bool moveLeft = false;
	Bar* enemyBar;
	//int indexbu;
	//int numBullet;
	int getPosX();
	int getPosY();
	void shoot2(int numberOfenemies);
	void shoot1(int numberOfenemies);
	void bulletMove(Player* item, int numberOfenemies, int& numberOfgettingShooted, int &points);
	bool getLife();
	void setLife(bool staute);
	
	void checkIfEnemyALife();
	void checkCollisionWithPlayerBullet(Bullet* playerBullet,int &numberOfHits, int &points);
protected:

private:
	bool life = true;
};

//for (;;)
	//{
	//	Say_Hello();
	//	// Sleep for 50*1000ms
	//	Sleep(50000);
	//}