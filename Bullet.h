#pragma once
#include "Player.h"
#include "Enemy.h"


extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

class Enemy;
class Player;

class Bullet:public Item
{
public:
	bool isLive = false;
	Enemy* father;
	//bool alive;// bool is true/false
	Bullet(SDL_Renderer* renderer, Enemy*f, int direction, bool live,bool enemyBullet);
	Bullet(SDL_Renderer* renderer, SDL_Rect p, int direction, bool live, bool playerBullet);
	Bullet();
	int directionX;
	//void handle_input(int xFire, int yFire);// pass where to fire bullet from
	//void move(int direction);
	void move(Player* player, int &numberOfgettingShooted, int &points);
	void move(int flag);
	//void show();
	void setxVel(int xV);
	void setyVel(int yV);
	int getxVel();
	int getyVel();
	void setPostionOfBullet(int x, int y);
	void checkCollision(Player* player, int& numberOfgettingShooted, int& points);
	void checkCollision(int flag);
	

protected:
	//Enemy enemyBullet;
	 
private:
	int xVel, yVel;
	
};
