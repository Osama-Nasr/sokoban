#include "Level.h"


Level::Level()
{
}

void Level::levelMode(Player* player, Bar* bar, SDL_Renderer* renderer, int level, bool& startCountingTimeForRehealing,
	double& rehealingTime, double worldTime, Enemy* enemies[], Bonuses* bonuses[], bool& continueMenu,
	double& bonusesTime, double& shootTime, double enemyShootEverySEC, int& numberOfgettingShooted, int& numberOfHits, int& points)
{
	player->move(player->getPlayerSpeedx(), player->getPlayerSpeedy());
	player->draw();
	player->bulletMove();
	bar->setSize(200 * player->blood, bar->getPos()->y / 12);
	bar->draw();
	bool allFalse = true;
	bool allTrue = true;



	//checking if the player got shoot and start counting rehealing time
	checkingPlayerGotShootStartCountingRehealingTime( player, startCountingTimeForRehealing, rehealingTime, worldTime);

	//checking if the enemeis got hit
	checkEnimesGotHit(enemies, player, numberOfHits, points, level);

	//checing if all the enimes are dead or not
	checkEnimesDead( enemies, allFalse, allTrue, level);

	//checking if the player is dead
	checkPlayerDead(player, allFalse, allTrue, continueMenu);

	//setting the postions of the enemies
	//printf("enemy life %d   posetion fo enemy:%d,%d\n", enemies[level]->getLife(), enemies[level]->getPosX(), enemies[level]->getPosY());
	settingPostionsOfEnemies(enemies, player, level, points, numberOfgettingShooted);
	
	//enemy shooting
	enemyShooting( level, enemies, worldTime, shootTime, enemyShootEverySEC);

	//counting the time for heart
	countingTimeForHeart(bonuses,worldTime,bonusesTime);

	//heart appearing
	heartAppearing(bonuses, player);

	SDL_RenderPresent(renderer);
	SDL_Delay(25);
}

void Level::enemyShooting( int const level, Enemy* enemies[], double worldTime, double& shootTime, double enemyShootEverySEC) {
	
	switch (level)
	{
	case 0:case 1: case 2:
	{
		if (worldTime - shootTime > enemyShootEverySEC)	 //the 1 is the second that every time the enemy will shoot
		{
			if (enemies[level]->getLife())
			{
				enemies[level]->shoot1(numberOfenemies);
			}
			shootTime = worldTime;
		}
	}
		break;
	case 3:
	{
		
		if (worldTime - shootTime > enemyShootEverySEC)	 //the 1 is the second that every time the enemy will shoot
		{
			for (int i = 0; i < numberOfenemies; i++)
			{
				if (enemies[i]->getLife())
				{
					if (i % 2 == 0)
						enemies[i]->shoot1(numberOfenemies);
					else if (i % 2 == 1)
						enemies[i]->shoot2(numberOfenemies);
				}
			}
			shootTime = worldTime;
		}
	}
		break;
	default:
		break;
	}
}

void Level::countingTimeForHeart(Bonuses* bonuses[],double worldTime, double& bonusesTime) {
	if (worldTime - bonusesTime > timeEveryBonusSEC)	 //the 1 is the second that bonuses will change place
	{
		for (int i = 0; i < numberOfBonuses; i++)
		{
			bonuses[i]->setPos(rand() % SCREEN_WIDTH, rand() % SCREEN_HEIGHT);
			bonuses[i]->setLife(true);
		}
		bonusesTime = worldTime;
	}
}

void Level::heartAppearing(Bonuses* bonuses[],Player* player) {

	for (int i = 0; i < numberOfBonuses; i++)
	{
		bonuses[i]->checkCollisionWithPlayer(player);
		if (bonuses[i]->getLife())
			bonuses[i]->draw();
	}
}

void Level::settingPostionsOfEnemies(Enemy* enemies[], Player* player, int const level, int& points, int& numberOfgettingShooted) {
	
	switch (level)
	{
	case 0: case 1:
	{
		if (enemies[level]->getLife()) {
			enemies[level]->enemyBar->setPos(enemies[level]->getPosX() + 15, enemies[level]->getPosY() - 20);
			if (enemies[level]->blood == 1.0f)
				enemies[level]->enemyBar->setSize(enemies[level]->enemyBar->getPos()->w, enemies[level]->enemyBar->getPos()->h);
			else
				enemies[level]->enemyBar->setSize(enemies[level]->enemyBar->getPos()->w * enemies[level]->blood, enemies[level]->enemyBar->getPos()->h);
			//printf("%d  %d\n",enemies[0]->enemyBar->getPos()->w, enemies[i]->enemyBar->getPos()->h);
			//printf("%d  \n",enemies[0]->blood);

			enemies[level]->enemyBar->draw();
			enemies[level]->draw();
			enemies[level]->bulletMove(player, numberOfenemies, numberOfgettingShooted, points);
		}
	}
	break;
	case 2:
	{
		if (enemies[level]->getLife()) {
			int px;
			if (enemies[level]->moveLeft)
				px = enemies[level]->getPosX() - 3;
			else
				px = enemies[level]->getPosX() + 3;

			if (px >= SCREEN_WIDTH - enemies[level]->getPos()->w)
				enemies[level]->moveLeft = true;
			else if (px <= enemies[level]->getPos()->w + 5)
				enemies[level]->moveLeft = false;

			enemies[level]->setPos(px, enemies[level]->getPosY());
			enemies[level]->enemyBar->setPos(enemies[level]->getPosX() + 15, enemies[1]->getPosY() - 20);
			if (enemies[level]->blood == 1.0f)
				enemies[level]->enemyBar->setSize(enemies[level]->enemyBar->getPos()->w, enemies[level]->enemyBar->getPos()->h);
			else
				enemies[level]->enemyBar->setSize(enemies[level]->enemyBar->getPos()->w * enemies[level]->blood, enemies[level]->enemyBar->getPos()->h);
			//printf("%d  %d\n",enemies[1]->enemyBar->getPos()->w, enemies[i]->enemyBar->getPos()->h);
			//printf("%d  \n",enemies[1]->blood);

			enemies[level]->enemyBar->draw();
			enemies[level]->draw();
			enemies[level]->bulletMove(player, numberOfenemies, numberOfgettingShooted, points);
		}
	}
	break;
	case 3:
	{
		for (int i = 0; i < numberOfenemies; i++)
		{
			if (enemies[i]->getLife()) {
				if (i == 2 || i == 4)
				{
					int px;
					if (enemies[i]->moveLeft)
						px = enemies[i]->getPosX() - 3;
					else
						px = enemies[i]->getPosX() + 3;

					if (px >= SCREEN_WIDTH - enemies[i]->getPos()->w)
						enemies[i]->moveLeft = true;
					else if (px <= enemies[i]->getPos()->w + 5)
						enemies[i]->moveLeft = false;

					enemies[i]->setPos(px, enemies[i]->getPosY());
				}
				enemies[i]->enemyBar->setPos(enemies[i]->getPosX() + 15, enemies[i]->getPosY() - 20);
				if (enemies[i]->blood == 1.0f)
					enemies[i]->enemyBar->setSize(enemies[i]->enemyBar->getPos()->w, enemies[i]->enemyBar->getPos()->h);
				else
					enemies[i]->enemyBar->setSize(enemies[i]->enemyBar->getPos()->w * enemies[i]->blood, enemies[i]->enemyBar->getPos()->h);
				//printf("%d  %d\n",enemies[0]->enemyBar->getPos()->w, enemies[i]->enemyBar->getPos()->h);
				//printf("%d  \n",enemies[0]->blood);
				enemies[i]->enemyBar->draw();
				enemies[i]->draw();
				enemies[i]->bulletMove(player, numberOfenemies, numberOfgettingShooted, points);
			}
		}
	}
	break;
	default:
		break;
	}
}

void Level::checkPlayerDead(Player* player,bool& allFalse, bool& allTrue, bool& continueMenu) {

	if (player->blood <= 0 || allFalse)
		continueMenu = 1;
	//printf("blood player:%f enemies are dead:%d continueMenu:%d\n", player.blood, allFalse, continueMenu);
	allFalse = true;
	allTrue = true;
}

void Level::checkEnimesDead(Enemy* enemies[],bool& allFalse, bool& allTrue, int const level) {

	switch (level)
	{
	case 0: case 1: case 2:
	{
		if (enemies[level]->getLife()) //a value is true
			allFalse = false; //not all values in array are false
		else //a value is false
			allTrue = false; //not all values in array are true
	}
	break;
	case 3:
	{
		for (int i = 0; i < numberOfenemies; i++) {
			if (enemies[i]->getLife()) //a value is true
				allFalse = false; //not all values in array are false
			else //a value is false
				allTrue = false; //not all values in array are true
			//printf("%d ", enemies[i]->getLife());
		}
	}
	default:
		break;
	}
}

void Level::checkEnimesGotHit(Enemy* enemies[], Player* player, int& numberOfHits, int& points, int const level) {

	switch (level)
	{
	case 0: case 1: case 2:
	{
		enemies[level]->checkCollisionWithPlayerBullet(player->bullet, numberOfHits, points);
		enemies[level]->checkIfEnemyALife();			// false mean that he is dead
	}
	break;
	case 3:
	{
		for (int i = 0; i < numberOfenemies; i++)
		{
			enemies[i]->checkCollisionWithPlayerBullet(player->bullet, numberOfHits, points);
			enemies[i]->checkIfEnemyALife();							// false mean that he is dead
		}
	}
	break;
	default:
		break;
	}
}

void Level::checkingPlayerGotShootStartCountingRehealingTime(Player* player, bool& startCountingTimeForRehealing, double& rehealingTime, double worldTime) {

	if (player->getPlayerJustgotHit())
	{
		if (startCountingTimeForRehealing) {
			rehealingTime = worldTime;
			startCountingTimeForRehealing = false;
		}

		if (worldTime - rehealingTime > rehealingAfterAHitSEC) {
			player->setPlayerJustgotHit(false);
			startCountingTimeForRehealing = true;
		}
	}

}