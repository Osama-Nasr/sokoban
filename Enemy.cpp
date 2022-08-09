#include "Enemy.h"
#include "Constants.h"

Enemy::Enemy(SDL_Renderer* renderer)
{
	blood = 1.0f;
	//indexbu = 0;
	isEnemy = true;
	setRenderer(renderer);
	loadImage("./enemyPicture.bmp");
	setPos(50, 50);
	setSize(50, 50);
	bullet = (Bullet**)malloc(10 * sizeof(Bullet));
	for (int i = 0; i < 10; i++)
	{
		bullet[i] = new Bullet(ren, this, directionBullet, false, true);
	}
	enemyBar = (Bar*)malloc(sizeof(Bar));
	enemyBar = new Bar(ren, pos);
}

Enemy::Enemy()
{
}

int Enemy::getPosX()
{
	return pos.x;
}

int Enemy::getPosY()
{
	return pos.y;
}

void Enemy::shoot2(int numberOfenemies)
{
	for (int i = 0; i < numberOfenemies; i++)
	{
		if (bullet[i]->isLive == false)
		{
			bullet[i]->setPos(pos.x, pos.y);
			directionBullet += 1;
			if (directionBullet > 4)
				directionBullet = -4;

			bullet[i]->directionX = directionBullet;
			bullet[i]->isLive = true;
			break;
		}
	}
}

void Enemy::shoot1(int numberOfenemies)
{
	for (int i = 0; i < numberOfenemies; i++)
	{
		if (bullet[i]->isLive == false)
		{
			bullet[i]->setPos(pos.x, pos.y);

			bullet[i]->isLive = true;
			break;
		}
	}
}

void Enemy::bulletMove(Player* item, int numberOfenemies,int &numberOfgettingShooted, int &points)
{
	for (int i = 0; i < numberOfenemies; i++)
	{
		if(bullet[i]->isLive)
			bullet[i]->move(item,numberOfgettingShooted,points);
	}
}

bool Enemy::getLife()
{
	return life;
}

void Enemy::setLife(bool staute)
{
	life = staute;
}

void Enemy::checkIfEnemyALife()
{
	if (blood <= 0.0f)
		setLife(false);
}

void Enemy::checkCollisionWithPlayerBullet(Bullet* playerBullet,int &numberOfHits, int &points)
{
	if (pos.x + 50 >= playerBullet->getPos()->x &&
		pos.x + 15 <= playerBullet->getPos()->x + playerBullet->getPos()->w &&
		pos.y + 15 >= playerBullet->getPos()->y &&
		pos.y + 15 <= playerBullet->getPos()->y + playerBullet->getPos()->h && getLife() == true)
	{
		playerBullet->isLive = false;
		playerBullet->setPos(1000, 1000);
		blood -= 1.0f;
		numberOfHits++;
		points += rewardPoints;
	}
}

//Enemy::~Enemy()
//{
//	if (image != NULL) {
		//SDL_DestroyTexture(image);
	//	image = NULL;
//	}
//}