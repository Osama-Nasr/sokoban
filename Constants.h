// Constants.h
#if !defined(MYLIB_CONSTANTS_H)
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

const int numberOfenemies = 7;		// the number of the enemies 
const int numberOfBonuses = 3;		// the number of the Bonuses 
const int numberOfLevels = 4;		// the number of the levels 
const int rewardPoints = 5;			// the points taht will be added to the player sscore when it hits somebody
const int hitDepletedPoints = 2;   //the points that will be taken from the player in case of getting hit
const int player_speed_init = 5;   //the inial spped of the player that it will start the game with
const int bullet_speed = 6;			//the spped of the bullets of both enemys and player
const double timeEveryBonusSEC = 8.0;			//the speed of the bullets of both enemys and player
const double rehealingAfterAHitSEC = 2.0;			//the spped of the bullets of both enemys and player

#endif