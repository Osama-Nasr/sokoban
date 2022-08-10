#pragma once
#pragma warning
#include "Draw.h"
#include "Actions.h"
#include "Time.h"
#include "Level.h"

using namespace std;
extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}


class Game{
private:
	int quit = 0;
	bool options = 0;
	bool mMenu = 1;
	int activeOption = 0;
	bool mContinueMenu = 0;
	int lvl = 3;

	double enemyShootEverySEC = 1.0;
	int numberOfHits = 0;
	int numberOfgettingShooted = 0;
	int points = 0;
	bool startCountingTimeForRehealing = true;
	double rehealingTime = 0;
	double shootTime = 0;
	double bonusesTime = 0;

	Player player;
	Draw text;
	Actions action;
	Time time;
	Level level;
	Bonuses** bonuses;
	Enemy** enemies;
	Bar bar;

	SDL_Renderer* renderer;
	SDL_Event event;
	SDL_Surface* screen;
	SDL_Surface* eti;
	SDL_Window* window;
	SDL_Texture* scrtex;
	int rc;

public:
	Game();
	~Game();
	void start();
	void menu();
	void game();
	void continueMenu();
	void updatingScreen();
};

