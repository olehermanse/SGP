#include "Game.h"

Game::Game(){
	gfx = new mGraphics(800,600);
	map = new mHeightmap(50,50);
	map->setSize(800, 600);
	map->randomizeZ(200);
	map->smooth();
	map->smooth();
	map->smooth();
	map->smooth();
	map->setColors();
	map->wrapToSphere(400);
	aVar = 0.0f;
	aSpeed = 0.6f;
	Player::gfx = gfx;
	player.coin = &coin;
	Coin::gfx = gfx;
}

void Game::handleEvents(){
	while( SDL_PollEvent( &event ) ){
		switch( event.type ){
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_ESCAPE){
					SDL_Quit();
					exit(0);
				}
				if(event.key.keysym.sym == SDLK_w)
					player.keyUp = true;
				if(event.key.keysym.sym == SDLK_a)
					player.keyLeft = true;
				if(event.key.keysym.sym == SDLK_s)
					player.keyDown = true;
				if(event.key.keysym.sym == SDLK_d)
					player.keyRight = true;
				if(event.key.keysym.sym == SDLK_SPACE)
					aSpeed = 0.0f;
				if(event.key.keysym.sym == SDLK_LEFT)
					aSpeed = 0.6f;
				if(event.key.keysym.sym == SDLK_RIGHT)
					aSpeed = -0.6f;
				if(event.key.keysym.sym == SDLK_r)
					aVar = 0.0f;
				if(event.key.keysym.sym == SDLK_1)
					gfx->cameraMode = 1;
				if(event.key.keysym.sym == SDLK_2)
					gfx->cameraMode = 2;
				if(event.key.keysym.sym == SDLK_3)
					gfx->cameraMode = 3;
				break;
			case SDL_KEYUP:
				if(event.key.keysym.sym == SDLK_w)
					player.keyUp = false;
				if(event.key.keysym.sym == SDLK_a)
					player.keyLeft = false;
				if(event.key.keysym.sym == SDLK_s)
					player.keyDown = false;
				if(event.key.keysym.sym == SDLK_d)
					player.keyRight = false;
				break;
			case SDL_QUIT:
				SDL_Quit();
				exit(0);
			default:
				break;
		}
	}
}

void Game::mainLoop(){
	while(1){
		handleEvents();
		aVar += aSpeed;
		gfx->startDrawing();
		glPushMatrix();
		if(gfx->cameraMode == 2){
			gfx->rotateCenter(360*player.theta/(2.0f*PI));
		}else
			gfx->rotateCenter(aVar);
		player.update();
		map->draw(gfx);
		glPopMatrix();
		player.draw();
		coin.draw();
		gfx->stopDrawing();
		SDL_Delay(17);
	}
}