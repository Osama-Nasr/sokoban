#pragma once
#include "Player.h"
#include "Bonuses.h"
#include "Enemy.h"
#include "Bar.h"
#include "Game.h"

class Level {
public:

	Level();
	void levelMode(Player* player, Bar* bar, SDL_Renderer* renderer, int level, bool& startCountingTimeForRehealing,
		double& rehealingTime, double worldTime, Enemy* enemies[], Bonuses* bonuses[], bool& continueMenu,
		double& bonusesTime, double& shootTime, double enemyShootEverySEC, int& numberOfgettingShooted, int& numberOfHits, int& points);
	void enemyShooting( int const level, Enemy* enemies[], double worldTime, double& shootTime, double enemyShootEverySEC);
	void countingTimeForHeart(Bonuses* bonuses[], double worldTime, double& bonusesTime);
	void heartAppearing(Bonuses* bonuses[], Player* player);
	void settingPostionsOfEnemies(Enemy* enemies[], Player* player, int const level, int& points, int& numberOfgettingShooted);
	void checkPlayerDead(Player* player, bool& allFalse, bool& allTrue, bool& continueMenu);
	void checkEnimesDead(Enemy* enemies[], bool& allFalse, bool& allTrue, int const level);
	void checkEnimesGotHit(Enemy* enemies[], Player* player, int& numberOfHits, int& points, int const level);
	void checkingPlayerGotShootStartCountingRehealingTime(Player* player, bool& startCountingTimeForRehealing, double& rehealingTime, double worldTime);
private:
	int nEnemies;
};