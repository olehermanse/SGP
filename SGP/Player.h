#ifndef __GameJam__Player__
#define __GameJam__Player__

#include "mGraphics.h"
#include "mHeightmap.h"
#include "Coin.h"

class Player{
public:
	Player();
	static mGraphics* gfx;
	bool keyUp;
	bool keyLeft;
	bool keyDown;
	bool keyRight;
	Coin* coin;
	
	float theta;
	float phi;
	float radius;
	mVector pos;
	mVector vel;
	mVector accel;
	float rot;
	float rotOffs;
	float deltaRot;
	float acc;
	
	void draw();
	void drawSpaceShip();
	void update();
	void rotate();
private:
	
};
#endif /* defined(__mGraphics__Player__) */
