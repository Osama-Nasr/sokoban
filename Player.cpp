#include "Player.h"
#include "Constants.h"

Player::Player(SDL_Renderer* renderer)
{
	isEnemy = false;
	blood = 1.0f;
	setRenderer(renderer);
	loadImage("./eti.bmp");
	setPos(320,370); //320,370
	setSize(50, 50);
	playerSpeedx = 0;
	playerSpeedy = 0;
	speedY_up = -(player_speed_init);
	speedY_down = (player_speed_init);
	speedX_right = (player_speed_init);
	speedX_left = -(player_speed_init);
	bullet = (Bullet*)malloc(sizeof(Bullet));
	//for (int i = 0; i < 1; i++)
	//{
		//bullet[i] = new Bullet(ren, pos, directionBullet, false, true);
	//}
	bullet = new Bullet(ren, pos, directionBullet, false, true);
};

Player::Player() {}

void Player::shoot()
{
	if (bullet->isLive == false)
	{
		bullet->setPos(pos.x, pos.y);

		bullet->isLive = true;
	}
}

void Player::bulletMove()
{
	int flag = 1;

	if (bullet->isLive)
		bullet->move(flag);

}

void Player::move(int x, int y)
{
	int tempx;
	int tempy;
	tempx = pos.x + x;
	tempy = pos.y + y;
	//if (tempx >= 0 && tempx <= SCREEN_HEIGHT &&  tempy <= SCREEN_WIDTH && tempy >= 0)    //this if i want to check the boarders of the window so the player won't go outside the window
//	{
		pos.x += x;
		pos.y += y;
	//}
}

void Player::setPlayerSpeedx(int PSx)
{
	playerSpeedx = PSx;
}

void Player::setPlayerSpeedy(int PSy)
{
	playerSpeedy = PSy;
}

void Player::setSpeedY_up(int SY_up)
{
	playerSpeedy = SY_up;
}

void Player::setSpeedY_down(int SY_down)
{
	playerSpeedy = SY_down;
}

void Player::setSpeedX_right(int SX_right)
{
	playerSpeedx = SX_right;
}

void Player::setSpeedX_left(int SX_left)
{
	playerSpeedx = SX_left;
}

int Player::getPlayerSpeedx()
{
	return playerSpeedx;
}

int Player::getPlayerSpeedy()
{
	return playerSpeedy;
}

int Player::getSpeedY_up()
{
	return speedY_up;
}

int Player::getSpeedY_down()
{
	return speedY_down;
}

int Player::getSpeedX_right()
{
	return speedX_right;
}

int Player::getSpeedX_left()
{
	return speedX_left;
}

void Player::increaseSpeedY_up()
{
	speedY_up--;
}

void Player::increaseSpeedY_down()
{
	speedY_down++;
}

void Player::increaseSpeedX_right()
{
	speedX_right++;
}

void Player::increaseSpeedX_left()
{
	speedX_left--;
}

void Player::decreaseSpeedY_up()
{
	speedY_up++;
}

void Player::decreaseSpeedY_down()
{
	speedY_down--;
}

void Player::decreaseSpeedX_right()
{
	speedX_right--;
}

void Player::decreaseSpeedX_left()
{
	speedX_left++;
}

void Player::setPlayerJustgotHit(bool staute)
{
	playerJustgotHit = staute;
}

bool Player::getPlayerJustgotHit()
{
	return playerJustgotHit;
}
