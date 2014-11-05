#ifndef __GameJam__Coin__
#define __GameJam__Coin__

#include "mGraphics.h"
#include "mHeightmap.h"

class Coin{
public:
	Coin();
	static mGraphics* gfx;
	
	float theta;
	float phi;
	float radius;
	mVector pos;
	
	void draw();
	void update();
	void rotate();
private:
	
};

#endif /* defined(__GameJam__Coin__) */
