#include "Game.h"

Game::Game()
{
	 rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
		&window, &renderer);

	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	SDL_SetWindowTitle(window, "Bullte hell 2 project");

	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
		0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING,SCREEN_WIDTH, SCREEN_HEIGHT);
	
	level = Level();
	player = Player(renderer);
	bar = Bar(renderer);
	text = Draw();
	action = Actions();
	time = Time();

	bonuses = (Bonuses**)malloc(numberOfBonuses * sizeof(Bonuses));
	for (int i = 0; i < numberOfBonuses; i++)
	{
		bonuses[i] = new Bonuses(renderer);
	}
	
	enemies = (Enemy**)malloc(numberOfenemies * sizeof(Enemy));
	for (int i = 0, j = 50, k = 50; i < numberOfenemies; i++, j += 80)
	{
		enemies[i] = new Enemy(renderer);
		enemies[i]->setPos(j, k);
		//enemies[i]->enemyBar->draw();
		if (i < 3)
		{
			k += 30;
		}
		else
			k -= 30;
	}

	time.setT1(SDL_GetTicks());
}

Game::~Game()
{
	delete enemies;
	delete bonuses;

	ItemQuit();
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

}


void Game::start()
{
	
	while (!quit) {

		menu();
		game();
		continueMenu();
	}
} 

void Game::menu()
{
	while (mMenu && !quit)
	{
		text.TextStartingMenu(screen, eti);

		while (options && !quit)
		{
			text.TextOptions(screen, eti, enemyShootEverySEC, activeOption, player, lvl);
			action.takeActionForOption(event, player, options,activeOption, enemyShootEverySEC, lvl, quit);
			updatingScreen();
		}

		action.takeActionStartingMenu(event, quit, options, mMenu);
		updatingScreen();		
	}
}

void Game::game()
{
	//game
	while (!mMenu && !quit && !mContinueMenu) {

		
		time.setT2(SDL_GetTicks());
		// here t2-t1 is the time in milliseconds since
		// the last screen was drawn
		// delta is the same time in seconds
		
		time.setDelta((time.getT2() - time.getT1()) * 0.001);
		time.setT1(time.getT2());//430 / 6 / fps

		time.setWorldTime(time.getWorldTime() + time.getDelta());

		//time distance += etiSpeed * delta;

		int black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
		SDL_FillRect(screen, NULL, black);

		time.setFpsTimer(time.getFpsTimer() + time.getDelta());

		if (time.getFpsTimer() > 0.5) {
			time.setFps(time.getFrames() * 2);
			time.setFrames(0);
			time.setFpsTimer(time.getFpsTimer() - 0.5 );
		};

		text.TextGame(screen, time.getWorldTime(), time.getFps(), numberOfHits, numberOfgettingShooted, points);

		updatingScreen();
	

		action.takePlayerActions(event, quit, player);
		
		level.levelMode(&player, &bar, renderer, lvl, startCountingTimeForRehealing,
			rehealingTime, time.getWorldTime(), enemies, bonuses, mContinueMenu,
			bonusesTime, shootTime, enemyShootEverySEC, numberOfgettingShooted, numberOfHits, points);

	}
}

void Game::continueMenu()
{
	text.TextContinueMenu(screen, eti, points);
	action.takeActionsContinueMenu(event, quit,mMenu,mContinueMenu, numberOfHits, numberOfgettingShooted, player, points, enemies, lvl);

	updatingScreen();
}

void Game::updatingScreen()
{
	SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
	//		SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, scrtex, NULL, NULL);
	SDL_RenderPresent(renderer);
}

