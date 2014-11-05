#ifndef __GameJam__mGraphics__
#define __GameJam__mGraphics__


#include "definitions.h"
#include "mPrimitives.h"

float myRandom(float min, float max);

class mGraphics{
public:
	const USHORT W;
	const USHORT H;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_RendererInfo info;
	
	mGraphics(USHORT w, USHORT h);
	
	
	void initSDL();
	
	void initGL();
	
	void startDrawing();
	void stopDrawing();
	void perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar );
	void translateToCenter();
	void translateToBottomLeft();
	void rotateCenter(float deg);
	
	void drawRect(int x, int y, float z, int w, int h);
	
	void drawCube(int x, int y, float z, int w, int h, int d);
	
	void draw4Verts(mVertex* a, mVertex* b, mVertex* c, mVertex* d);
	
	char cameraMode;
private:
	
};

#endif /* defined(__mGraphics__mGraphics__) */
