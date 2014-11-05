#include "mGraphics.h"
#include "mHeightmap.h"
#include "Game.h"

int main(int argc, char** argv){
	srand(time(0));
	Game* game = new Game();
	game->mainLoop();
	return 0;
}
