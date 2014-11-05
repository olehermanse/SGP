#ifndef __GameJam__Game__
#define __GameJam__Game__

#include "mGraphics.h"
#include "mHeightmap.h"
#include "Player.h"
#include "Coin.h"

class Game{
public:
	Game();
	mHeightmap* map;
	mGraphics* gfx;
	Player player;
	Coin coin;
	float aVar;
	float aSpeed;
	SDL_Event event;
	void mainLoop();
	void handleEvents();
private:
	
};

#endif /* defined(__mGraphics__Game__) */
