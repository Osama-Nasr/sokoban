#define _USE_MATH_DEFINES
#include<math.h>
#include<stdio.h>
#include<string.h>
#include"Item.h"
#include"Player.h"
#include "Enemy.h"
#include "Bar.h"
#include "Bonuses.h"
#include "Level.h"
#include "Game.h"
#include <stdlib.h>
#include <time.h>

int t1, t2;
double delta, distance,worldTime;

extern "C" {
#include"./SDL2-2.0.10/include/SDL.h"
#include"./SDL2-2.0.10/include/SDL_main.h"
}


// narysowanie napisu txt na powierzchni screen, zaczynaj¹c od punktu (x, y)
// charset to bitmapa 128x128 zawieraj¹ca znaki
// draw a text txt on surface screen, starting from the point (x, y)
// charset is a 128x128 bitmap containing character images
void DrawString(SDL_Surface *screen, int x, int y, const char *text,
                SDL_Surface *charset) {
	int px, py, c;
	SDL_Rect s, d;
	s.w = 8;
	s.h = 8;
	d.w = 8;
	d.h = 8;
	while(*text) {
		c = *text & 255;
		px = (c % 16) * 8;
		py = (c / 16) * 8;
		s.x = px;
		s.y = py;
		d.x = x;
		d.y = y;
		SDL_BlitSurface(charset, &s, screen, &d);
		x += 8;
		text++;
		};
	};


// narysowanie na ekranie screen powierzchni sprite w punkcie (x, y)
// (x, y) to punkt œrodka obrazka sprite na ekranie
// draw a surface sprite on a surface screen in point (x, y)
// (x, y) is the center of sprite on screen
void DrawSurface(SDL_Surface *screen, SDL_Surface *sprite, int x, int y) {
	SDL_Rect dest;
	dest.x = x - sprite->w / 2;
	dest.y = y - sprite->h / 2;
	dest.w = sprite->w;
	dest.h = sprite->h;
	SDL_BlitSurface(sprite, NULL, screen, &dest);
	};


// rysowanie pojedynczego pixela
// draw a single pixel
void DrawPixel(SDL_Surface *surface, int x, int y, Uint32 color) {
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	*(Uint32 *)p = color;
	};


// rysowanie linii o d³ugoœci l w pionie (gdy dx = 0, dy = 1) 
// b¹d?poziomie (gdy dx = 1, dy = 0)
// draw a vertical (when dx = 0, dy = 1) or horizontal (when dx = 1, dy = 0) line
void DrawLine(SDL_Surface *screen, int x, int y, int l, int dx, int dy, Uint32 color) {
	for(int i = 0; i < l; i++) {
		DrawPixel(screen, x, y, color);
		x += dx;
		y += dy;
		};
	};


// rysowanie prostok¹ta o d³ugoœci boków l i k
// draw a rectangle of size l by k
void DrawRectangle(SDL_Surface *screen, int x, int y, int l, int k,
                   Uint32 outlineColor, Uint32 fillColor) {
	int i;
	DrawLine(screen, x, y, k, 0, 1, outlineColor);
	DrawLine(screen, x + l - 1, y, k, 0, 1, outlineColor);
	DrawLine(screen, x, y, l, 1, 0, outlineColor);
	DrawLine(screen, x, y + k - 1, l, 1, 0, outlineColor);
	for(i = y + 1; i < y + k - 1; i++)
		DrawLine(screen, x + 1, i, l - 2, 1, 0, fillColor);
	};

//void shootingFromEnemy(int i, Bullet enemyBullets[]) {
//		
//		enemyBullets[i].move();
//		enemyBullets[i].draw();	
//}
//add enemy function 
			
bool checkingAllEnemiesAreLife(Enemy* enemies[]) {		//checking if he all enemies are dead or not if yes he won and close the 
	bool allALife = true;
	for (int i = 0; i < numberOfenemies; i++)
	{
		if (!enemies[i]->getLife())
		{
			allALife = false;
		}
	}
	return allALife;
}

//bool checkingAllEnemiesAreLife(Enemy* enemies[]) {		//checking if he all enemies are dead or not if yes he won and close the 
//	printf("HI Nasr");
//	return true;
//}

// main	
#ifdef __cplusplus
extern "C"
#endif
int main(int argc, char **argv) {
	
	Game game;
	game.start();
	/*int quit, frames, rc, activeOption, points, numberOfHits, numberOfgettingShooted, level;
	double fpsTimer, fps, etiSpeed, enemyShootEverySEC;
	bool menu,options, continueMenu, startCountingTimeForRehealing;
	double shootTime = 0, bonusesTime = 0, rehealingTime = 0;
	SDL_Event event;
	SDL_Surface *screen, *charset;
	SDL_Surface *eti;
	SDL_Texture *scrtex;
	SDL_Window *window;
	SDL_Window *window2;
	SDL_Renderer *renderer;
	//SDL_Renderer *screen2 = SDL_CreateRenderer(window,-1,0);

	level = 3;
	points = 0;
	frames = 0;
	fpsTimer = 0;
	fps = 0;
	quit = 0;
	menu = 1;
	options = 0;
	worldTime = 0;
	distance = 0;
	etiSpeed = 1;
	enemyShootEverySEC = 1.0;
	continueMenu = 0;
	activeOption = 0;
	numberOfHits = 0; 
	numberOfgettingShooted = 0;
	startCountingTimeForRehealing = true;
	bool allTrue = true;
	bool allFalse = true;
	// okno konsoli nie jest widoczne, je¿eli chcemy zobaczy?
	// komunikaty wypisywane printf-em trzeba w opcjach:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// zmieni?na "Console"
	// console window is not visible, to see the printf output
	// the option:
	// project -> szablon2 properties -> Linker -> System -> Subsystem
	// must be changed to "Console"
	printf("wyjscie printfa trafia do tego okienka\n");
	printf("printf output goes here\n");

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("SDL_Init error: %s\n", SDL_GetError());
		return 1;
	}

	// tryb pe³noekranowy / fullscreen mode
//	rc = SDL_CreateWindowAndRenderer(0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP,
//	                                 &window, &renderer);
	rc = SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0,
	                                 &window, &renderer);
	if(rc != 0) {
		SDL_Quit();
		printf("SDL_CreateWindowAndRenderer error: %s\n", SDL_GetError());
		return 1;
		};
	
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
	SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	SDL_SetRenderDrawColor(renderer, 0,0,0, 255 );

	SDL_SetWindowTitle(window, "Bullte hell 2 project");


	screen = SDL_CreateRGBSurface(0, SCREEN_WIDTH, SCREEN_HEIGHT, 32,
	                              0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	scrtex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888,
	                           SDL_TEXTUREACCESS_STREAMING,
							   SCREEN_WIDTH, SCREEN_HEIGHT);
	srand(time(0));


	// wy³¹czenie widocznoœci kursora myszy
	//SDL_ShowCursor(SDL_DISABLE);

	// wczytanie obrazka cs8x8.bmp
	charset = SDL_LoadBMP("./cs8x8.bmp");
	if(charset == NULL) {
		printf("SDL_LoadBMP(cs8x8.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
		};
	SDL_SetColorKey(charset, true, 0x000000);

		eti = SDL_LoadBMP("./eti.bmp");
		//printf("%d", eti->w);
	if(eti == NULL) {
		printf("SDL_LoadBMP(eti.bmp) error: %s\n", SDL_GetError());
		SDL_FreeSurface(charset);
		SDL_FreeSurface(screen);
		SDL_DestroyTexture(scrtex);
		SDL_DestroyWindow(window);
		SDL_DestroyRenderer(renderer);
		SDL_Quit();
		return 1;
	};

	Player player(renderer);
	Bar bar(renderer);

	//Level** enemies = (Enemy**)malloc(numberOfenemies * sizeof(Enemy));

	Bonuses** bonuses = (Bonuses**)malloc(numberOfBonuses * sizeof(Bonuses));
	for (int i = 0; i < numberOfBonuses; i++)
	{
		bonuses[i] = new Bonuses(renderer);
	}
	
	Level levels;

	Enemy **enemies = (Enemy**)malloc(numberOfenemies *sizeof(Enemy));
	//memset(enemies, 0, 10*sizeof(Enemy));
	for (int i = 0, j = 50,k=50; i < numberOfenemies; i++, j += 80)
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
	
	//Bullet enemyBullet1(renderer, enemy1.getPosX());
	//Bullet enemyBullets[1000];
	//memset(enemyBullets, 0, 1000 * sizeof(Bullet));
	//for (int i = 0; i < numberOfenemies; i++) //insilaing the array to the constucor object
	//	enemyBullets[i] = enemyBullet1;

	//for ( int i = 0; i <numberOfenemies; i++)
	//{
	//	enemyBullets[i].setPostionOfBullet(enemies[i].getPosX() + 25, enemies[i].getPosY());			//inizilating the postions of the bullets to the postios of the enemeies
	//}

	char text[128];
	int black = SDL_MapRGB(screen->format, 0x00, 0x00, 0x00);
	int green = SDL_MapRGB(screen->format, 0x00, 0xFF, 0x00);
	int red = SDL_MapRGB(screen->format, 0xFF, 0x00, 0x00);
	int blue  = SDL_MapRGB(screen->format, 0x11, 0x11, 0xCC);

	t1 = SDL_GetTicks();
	
	//start
	while(!quit) {
		//SDL_FillRect(screen,NULL,blue);
		
		//menu
		while (menu && !quit)
		{
			DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, SCREEN_HEIGHT - 8, red, blue);
			DrawSurface(screen, eti, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 150);
			sprintf(text, "Welcome to Bullet Hell game");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 2 - 30, text, charset);
			sprintf(text, "Press O for options");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 2, text, charset);
			sprintf(text, "Press S to start the game");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 2 + 30, text, charset);
			while (options && !quit)
			{
				DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, SCREEN_HEIGHT - 8, red, blue);
				DrawSurface(screen, eti, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 180);
				DrawRectangle(screen, 150, screen->h / 2 - 30 + (activeOption * 30), 10, 10, red, red);
				sprintf(text, "Info catalog (press O to go back)");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 2 - 60, text, charset);
				sprintf(text, "1. Speed of the player (0...10): %d", player.getSpeedY_down());
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 2 - 30, text, charset);
				sprintf(text, "2. shooting from enemy every sec: %3.2f", enemyShootEverySEC );
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 2, text, charset);
				sprintf(text, "3. level: %d", level+1);
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 2 + 30, text, charset);
				/*sprintf(text, "4. Initial horizontal speed: ");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 2 + 60, text, charset);
				sprintf(text, "5. Dash speed: ");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 2 + 90, text, charset);
				sprintf(text, "6. Dash cooldown: ");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 2 + 120, text, charset);
				sprintf(text, "7. Jump speed: ");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 2 + 150, text, charset);
				sprintf(text, "8. Number of stars: ");
				DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 2 + 180, text, charset);

				while (SDL_PollEvent(&event)) {
					switch (event.type) {
					case SDL_KEYDOWN:
						if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
						else if (event.key.keysym.sym == SDLK_o)
						{
							options = (options + 1) % 2;
						}
						else if (event.key.keysym.sym == SDLK_UP)
						{
							switch (activeOption) {
							case 0:
								player.increaseSpeedX_left();
								player.increaseSpeedX_right();
								player.increaseSpeedY_down();
								player.increaseSpeedY_up();
								break;
							case 1:
								enemyShootEverySEC += 0.5;
								break;
							case 2:
								level += 1;
								break;
							case 3:
								break;
							case 4:
								break;
							case 5:
								break;
							case 6:
								break;
							case 7:
								break;
							}
						}
						else if (event.key.keysym.sym == SDLK_DOWN)
						{
							switch (activeOption) {
							case 0:
								
								player.decreaseSpeedX_left();
								player.decreaseSpeedX_right();
								player.decreaseSpeedY_down();
								player.decreaseSpeedY_up();
								break;
							case 1:
								enemyShootEverySEC -= 0.5;
								break;
							case 2:
								level -= 1;
								break;
							case 3:
								break;
							case 4:
								break;
							case 5:
								break;
							case 6:
								break;
							case 7:
								break;
							}
						}
						else if (event.key.keysym.sym == SDLK_1)
						{
							activeOption = 0;
						}
						else if (event.key.keysym.sym == SDLK_2)
						{
							activeOption = 1;
						}
						else if (event.key.keysym.sym == SDLK_3)
						{
							activeOption = 2;
						}
						else if (event.key.keysym.sym == SDLK_4)
						{
							activeOption = 3;
						}
						else if (event.key.keysym.sym == SDLK_5)
						{
							activeOption = 4;
						}
						else if (event.key.keysym.sym == SDLK_6)
						{
							activeOption = 5;
						}
						else if (event.key.keysym.sym == SDLK_7)
						{
							activeOption = 6;
						}
						else if (event.key.keysym.sym == SDLK_8)
						{
							activeOption = 7;
						}
						break;
					case SDL_KEYUP:
						break;
					case SDL_QUIT:
						quit = 1;
						break;
					};
				}
				SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
				//		SDL_RenderClear(renderer);
				SDL_RenderCopy(renderer, scrtex, NULL, NULL);
				SDL_RenderPresent(renderer);
			}
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
					else if (event.key.keysym.sym == SDLK_d)
					{
						//movementMode = (movementMode + 1) % 2;
					}
					else if (event.key.keysym.sym == SDLK_o)
					{
						options = (options + 1) % 2;
					}
					else if (event.key.keysym.sym == SDLK_s)
					{
						menu = 0;
						//points = 0;
						//heartCount = 0;
					}
					break;
				case SDL_KEYUP:
					break;
				case SDL_QUIT:
					quit = 1;
					break;
				};
			};
			SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
			//		SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, scrtex, NULL, NULL);
			SDL_RenderPresent(renderer);
		}

		//game
		while (!menu && !quit && !continueMenu) {
			
			t2 = SDL_GetTicks();
			// w tym momencie t2-t1 to czas w milisekundach,
			// jaki uplyna?od ostatniego narysowania ekranu
			// delta to ten sam czas w sekundach
			// here t2-t1 is the time in milliseconds since
			// the last screen was drawn
			// delta is the same time in seconds
			delta = (t2 - t1) * 0.001;
			t1 = t2;//430 / 6 / fps

			worldTime += delta;

			distance += etiSpeed * delta;

			SDL_FillRect(screen, NULL, black);

		//	DrawSurface(screen, eti,
		//		SCREEN_WIDTH / 3 + sin(distance) * SCREEN_HEIGHT / 3,
		//		SCREEN_HEIGHT / 4 + cos(distance) * SCREEN_HEIGHT / 3);

			fpsTimer += delta;
			if (fpsTimer > 0.5) {
				fps = frames * 2;
				frames = 0;
				fpsTimer -= 0.5;
			};

			// tekst informacyjny / options text
			DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, 36, red, blue);
			//            "template for the second project, elapsed time = %.1lf s  %.0lf frames / s"
			sprintf(text, "Esc - exit, elapsed time = %.1lf s  %.0lf frames / s", worldTime, fps);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 10, text, charset);
			//	      "Esc - exit, \030 - faster, \031 - slower"
			sprintf(text, "space for shooting, hits: %d, got hit: %d, Total points: %d",numberOfHits,numberOfgettingShooted , points);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, 26, text, charset);

			SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
			//		SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, scrtex, NULL, NULL);
			SDL_RenderPresent(renderer);
			//check the collion of the player with any enemy bullet or 
			//if (SDL_HasIntersection(player.getPos(), enemyBullets[0].getPos()) || SDL_HasIntersection(player.getPos(), enemies[0].getPos()))
			//{
			//	continueMenu = 1;
			//}
			// obs³uga zdarze?(o ile jakie?zasz³y) / handling of events (if there were any)
			//SDL_HasIntersection(player.getPos(),bu)
			
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym)
					{
						case SDLK_UP:
							player.setPlayerSpeedy(player.getSpeedY_up());
							break;
						case SDLK_DOWN:
							player.setPlayerSpeedy(player.getSpeedY_down());
							break;
						case SDLK_RIGHT:
							player.setPlayerSpeedx(player.getSpeedX_right());
							break;
						case SDLK_LEFT:
							player.setPlayerSpeedx(player.getSpeedX_left());
							break;
						case SDLK_SPACE:
							player.shoot();
							break;
						case SDLK_ESCAPE:
							quit = 1;
					default:
						break;
					}
					break;
				case SDL_KEYUP:
					switch (event.key.keysym.sym)
					{
					case SDLK_UP:
						player.setPlayerSpeedy(0);
						break;
					case SDLK_DOWN:
						player.setPlayerSpeedy(0);
						break;
					case SDLK_RIGHT:
						player.setPlayerSpeedx(0);
						break;
					case SDLK_LEFT:
						player.setPlayerSpeedx(0);
						break;
					case SDLK_ESCAPE:
						quit = 1;
						break;
					default:
						break;
					}
					break;
				case SDL_QUIT:
					quit = 1;
					break;
				};
				
				//SDL_Delay(20);
			};

			
			levels.levelMode(&player, &bar, renderer, level, startCountingTimeForRehealing,
					rehealingTime, worldTime, enemies, bonuses, continueMenu,
					bonusesTime, shootTime, enemyShootEverySEC, numberOfgettingShooted, numberOfHits, points);
			
		}

		//continue Menu and playing again 
		while (continueMenu && !quit)
		{
			DrawRectangle(screen, 4, 4, SCREEN_WIDTH - 8, SCREEN_HEIGHT - 8, red, blue);
			DrawSurface(screen, eti, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 150);
			sprintf(text, "Continue? Press c if so, or press ESC to exit, or press n for menu");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 2 - 30, text, charset);
			sprintf(text, "Your score is %d", points);
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 2, text, charset);
			sprintf(text, "want to go to level 1 press 1 & level 2 press 2 and so on");
			DrawString(screen, screen->w / 2 - strlen(text) * 8 / 2, screen->h / 2 + 30, text, charset);
			
			while (SDL_PollEvent(&event)) {
				switch (event.type) {
				case SDL_KEYDOWN:
					if (event.key.keysym.sym == SDLK_ESCAPE) quit = 1;
					/*else if (event.key.keysym.sym == SDLK_d)
					{
						movementMode = (movementMode + 1) % 2;
					}
					else if (event.key.keysym.sym == SDLK_n)
					{
						menu = 1;
						continueMenu = 0;
						numberOfHits = 0;
						numberOfgettingShooted = 0;
						player.blood = 1.0f;
						points = 0;
						player.setPos(320, 370);
						for (int i = 0; i < numberOfenemies; i++)
						{
							enemies[i]->blood = 1.0f;
							enemies[i]->setLife(true);
						}
					}
					else if (event.key.keysym.sym == SDLK_c)
					{
						player.setPos(320, 370);
						continueMenu = 0;
						points = 0;
						player.blood = 1.0f;
						for (int i = 0; i < numberOfenemies; i++)
						{
							enemies[i]->blood = 1.0f;
							enemies[i]->setLife(true);
						}
					}
					else if (event.key.keysym.sym == SDLK_1)
					{
						player.setPos(320, 370);
						continueMenu = 0;
						points = 0;
						player.blood = 1.0f;
						level = 0;
						for (int i = 0; i < numberOfenemies; i++)
						{
							enemies[i]->blood = 1.0f;
							enemies[i]->setLife(true);
						}
					}
					else if (event.key.keysym.sym == SDLK_2)
					{
						player.setPos(320, 370);
						continueMenu = 0;
						points = 0;
						player.blood = 1.0f;
						level = 1;
						for (int i = 0; i < numberOfenemies; i++)
						{
							enemies[i]->blood = 1.0f;
							enemies[i]->setLife(true);
						}
					}
					else if (event.key.keysym.sym == SDLK_3)
					{
						player.setPos(320, 370);
						continueMenu = 0;
						points = 0;
						player.blood = 1.0f;
						level = 2;
						for (int i = 0; i < numberOfenemies; i++)
						{
							enemies[i]->blood = 1.0f;
							enemies[i]->setLife(true);
						}
					}
					else if (event.key.keysym.sym == SDLK_4)
					{
						player.setPos(320, 370);
						continueMenu = 0;
						points = 0;
						player.blood = 1.0f;
						level = 3;
						for (int i = 0; i < numberOfenemies; i++)
						{
							enemies[i]->blood = 1.0f;
							enemies[i]->setLife(true);
						}
					}
					break;
				case SDL_KEYUP:
					//etiSpeed = 1.0;
					break;
				case SDL_QUIT:
					quit = 1;
					break;
				};
			};
			SDL_UpdateTexture(scrtex, NULL, screen->pixels, screen->pitch);
			//		SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, scrtex, NULL, NULL);
			SDL_RenderPresent(renderer);
		}		
	};
		
	// zwolnienie powierzchni / freeing all surfaces
	
	ItemQuit();
	SDL_FreeSurface(charset);
	SDL_FreeSurface(screen);
	SDL_DestroyTexture(scrtex);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit(); */
	return 0;
};
