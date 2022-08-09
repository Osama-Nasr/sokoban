#pragma once
#include "Game.h"

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}

class Actions
{
public:
	void takeActionForOption(SDL_Event event, Player& player, bool options, int activeOption,
		double& enemyShootEverySEC, int& level, int& quit);
	void takeActionStartingMenu(SDL_Event event, int& quit, bool& options, bool& mMenu);
	void takePlayerActions(SDL_Event event, int& quit, Player player);
	void takeActionsContinueMenu(SDL_Event event, int& quit, bool& mMenu, bool& mContinueMenu, int& numberOfHits, int& numberOfgettingShooted
		, Player& player, int& points, Enemy** enemies, int& lvl);

	Actions();
	~Actions();
};

