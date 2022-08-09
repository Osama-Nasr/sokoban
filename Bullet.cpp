//#pragma once
#include "Enemy.h"
#include "Constants.h"

extern double worldTime;

Bullet::Bullet(SDL_Renderer* renderer, Enemy* f,int direction, bool live, bool enenyBullet)// set initial values for all data members
{
	isEnemy = enenyBullet;
	isLive = live;
	father = f;
	directionX = direction;
	//alive = false;
	//enemyBullet.pos.x = ;
	setRenderer(renderer);
	loadImage("./bullet.bmp");
	//setPos(x,y); 
	setSize(10, 10);
	setPos(1000, 1000);
	xVel = pos.x + 25;
	yVel = bullet_speed;		 // this will be the bullet speed
	
}

Bullet::Bullet(SDL_Renderer* renderer, SDL_Rect p, int direction, bool live, bool playerBullet)// set initial values for all data members
{
	isPlayer = playerBullet;
	isLive = live;
	directionX = direction;
	//alive = false;
	//enemyBullet.pos.x = ;
	setRenderer(renderer);
	loadImage("./bullet.bmp");
	//setPos(x,y); 
	setSize(10, 10);
	setPos(1000, 1000);
	xVel = pos.x + 25;
	yVel = -(bullet_speed);	   // this will be the bullet speed
	
}

Bullet::Bullet()
{
}

void Bullet::setxVel(int xV)
{
	xVel = xV;
}

void Bullet::setyVel(int yV)
{
	yVel = yV;
}

int Bullet::getxVel()
{
	return xVel;
}

int Bullet::getyVel()
{
	return yVel;
}

void Bullet::setPostionOfBullet(int x, int y)
{
	setPos(x, y);
}

//void Bullet::handle_input(int xFire, int yFire)
//{
//	if (alive == true) return;
//	//if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
//	{
//		x = xFire;
//		y = yFire;
//		alive = true;
//	}
//}

//void Bullet::move(int direction)
//{
//	directionX = direction;
//	if (pos.y < SCREEN_HEIGHT) {
//		pos.x += direction;
//		pos.y += yVel;
//	}
//	else
//	{
//		SDL_DestroyTexture(image);
//		//~Bullet(); //setPostionOfBullet(pos.x, 50);
//	}
//}
void Bullet::move(Player* player, int &numberOfgettingShooted, int &points)
{
	if (pos.y < SCREEN_HEIGHT && pos.x < SCREEN_WIDTH) {
		pos.x += directionX;
		pos.y += yVel;
		draw();

		checkCollision(player, numberOfgettingShooted,points);
	}
	else
	{
		this->isLive = false;
		//delete this;
		//SDL_DestroyTexture(image);
		//~Bullet(); //setPostionOfBullet(pos.x, 50);
	}
}

void Bullet::move(int flag)
{
	if (pos.y > 0 && pos.x > 0) {
		pos.x += directionX;
		pos.y += yVel;
		draw();
		checkCollision(flag);
	}
	else
	{
		this->isLive = false;
		//delete this;
		//SDL_DestroyTexture(image);
		//~Bullet(); //setPostionOfBullet(pos.x, 50);
	}
}

void Bullet::checkCollision(Player* player, int &numberOfgettingShooted, int& points)
{
//	int i = 0;
	//while (i<10) //ten enemies
	//{ 
	if (!player->getPlayerJustgotHit())
	{
		if (pos.x + 5 >= player->getPos()->x &&
			pos.x + 5 <= player->getPos()->x + player->getPos()->w &&
			pos.y + 5 >= player->getPos()->y &&
			pos.y + 5 <= player->getPos()->y + player->getPos()->h)
		{
			this->isLive = false;
			setPos(1000, 1000);
			player->blood -= 0.2f;
			numberOfgettingShooted++;
			points -= hitDepletedPoints;
			player->setPlayerJustgotHit(true);
			//break;
		}
	}
		
	//	i++;
//	}
}

void Bullet::checkCollision(int flag)
{	

		//if (pos.x + 5 >= enemies->getPos()->x &&
		//	pos.x + 5 <= enemies->getPos()->x + enemies->getPos()->w &&
		//	pos.y + 5 >= enemies->getPos()->y &&
		//	pos.y + 5 <= enemies->getPos()->y + enemies->getPos()->h)
		//{
		//	this->isLive = false;
		//	setPos(1000, 1000);
		//	enemies->blood -= 0.2f;
		//	//break;
		//}
	//	i++;
//	}
}

