#include "mGraphics.h"

float myRandom(float min, float max){
	float ret = 0.0f;
	int res = 10000;
	int r = rand()%res;
	float range = max - min;
	ret = ((float)r*range/(float)res) + min;
	return ret;
}

mGraphics::mGraphics(USHORT w, USHORT h):
W(w),
H(h){
	cameraMode = 1;
	initSDL();
	initGL();
}


void mGraphics::initSDL(){
	srand((int)time(0));
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_CreateWindowAndRenderer(W, H, SDL_WINDOW_OPENGL, &(window), &(renderer));
	SDL_GetRendererInfo(renderer, &info);
	/*TODO: Check that we have OpenGL */
	if ((info.flags & SDL_RENDERER_ACCELERATED) == 0 ||
		(info.flags & SDL_RENDERER_TARGETTEXTURE) == 0) {
		/*TODO: Handle this. We have no render surface and not accelerated. */
	}
	
	/* Enable smooth shading */
	glShadeModel( GL_SMOOTH );
 
	/* Set the background black */
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
 
	/* Depth buffer setup */
	glClearDepth( 1.0f );
 
	/* Enables Depth Testing */
	glEnable( GL_DEPTH_TEST );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
 
	/* The Type Of Depth Test To Do */
	glDepthFunc( GL_LEQUAL );
 
	/* Really Nice Perspective Calculations */
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
	SDL_GL_SetSwapInterval(1);
}

void mGraphics::initGL(){
	/* Height / width ration */
	GLfloat ratio;
 
 
	ratio = ( GLfloat )W / ( GLfloat )H;
 
	/* Setup our viewport. */
	glViewport( 0, 0, ( GLsizei )W, ( GLsizei )H );
 
	/* change to the projection matrix and set our viewing volume. */
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
 
	/* Set our perspective */
	perspectiveGL( 45.0f, ratio, 5.0f, 3000.0f );
 
	/* Make sure we're chaning the model view and not the projection */
	glMatrixMode( GL_MODELVIEW );
 
	/* Reset The View */
	glLoadIdentity( );
}

void mGraphics::startDrawing(){
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	
	//Prepare for matrix operations
	glLoadIdentity();
	if(cameraMode == 1 || cameraMode == 2){//"3D" view
		glTranslatef( 0.0f, 0.0f, -1.0f*((float)H-1.0f)*(0.5f/(sqrt(2)-1)));
		glScalef(0.5f, 0.5f, 0.5f);
		glRotatef(-60.0f, 1, 0, 0);
	}else{//2D view
		glTranslatef( 0.0f,0.0f, -1.0f*((float)H-1.0f)*(0.5f/(sqrt(2)-1)));
	}
	translateToBottomLeft();
}

void mGraphics::stopDrawing(){
	SDL_GL_SwapWindow(window);
}


void mGraphics::perspectiveGL( GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar )
{
	const GLdouble pi = 3.1415926535897932384626433832795;
	
	GLdouble fW, fH;
	fH = tan( (fovY / 2) / 180 * pi ) * zNear;
	fH = tan( fovY / 360 * pi ) * zNear;
	fW = fH * aspect;
	glFrustum( -fW, fW, -fH, fH, zNear, zFar );
}

void mGraphics::translateToCenter(){
	glTranslatef( 0.5f*(float)W,0.5f*(float)H,0.0f);
}

void mGraphics::translateToBottomLeft(){
	glTranslatef( -0.5f*(float)W,-0.5f*(float)H,0.0f);
}

void mGraphics::rotateCenter(float deg){
	translateToCenter();
	glRotatef(deg, 0,0,1);
	translateToBottomLeft();
}

void mGraphics::drawRect(int x, int y, float z, int w, int h){
	float fX = (float)x;
	float fY = (float)y;
	float fZ = (float)z;
	
	glBegin( GL_QUADS );                /* Draw A Quad */
	glVertex3f( fX,  fY, fZ);			/* Top Left */
	glVertex3f(  fX+w,  fY, fZ);		/* Top Right */
	glVertex3f(  fX+w, fY+h, fZ);		/* Bottom Right */
	glVertex3f( fX, fY+h, fZ);			/* Bottom Left */
	glEnd( );
}

void mGraphics::drawCube(int x, int y, float z, int w, int h, int d){
	float fX = (float)x;
	float fY = (float)y;
	float fZ = (float)z;
	float fW = (float)w;
	float fH = (float)h;
	float fD = (float)d;
	glTranslatef(fX,fY,fZ);
	fX = -fW/2;
	fY = -fH/2;
	//Back
	glBegin( GL_QUADS );							/* Draw A Quad */
	glVertex3f(		fX,		fY,		fZ);			/* Top Left */
	glVertex3f(		fX+fW,  fY,		fZ);			/* Top Right */
	glVertex3f(		fX+fW,	fY+fH,	fZ);			/* Bottom Right */
	glVertex3f(		fX,		fY+fH,	fZ);			/* Bottom Left */
	glEnd( );
	//Bot
	glBegin( GL_QUADS );							/* Draw A Quad */
	glVertex3f(		fX+fW,	fY+fH,	fZ);			/* Bottom Right */
	glVertex3f(		fX,		fY+fH,	fZ);			/* Bottom Left */
	glVertex3f(		fX,		fY+fH,	fZ+fD);			/* Bottom Left */
	glVertex3f(		fX+fW,	fY+fH,	fZ+fD);			/* Bottom Right */
	glEnd( );
	//Left
	glBegin( GL_QUADS );							/* Draw A Quad */
	glVertex3f(		fX,		fY,		fZ);			/* Top Left */
	glVertex3f(		fX,		fY+fH,	fZ);			/* Bottom Left */
	glVertex3f(		fX,		fY+fH,	fZ+fD);			/* Bottom Left */
	glVertex3f(		fX,		fY,		fZ+fD);			/* Top Left */
	glEnd( );
	//Right
	glBegin( GL_QUADS );							/* Draw A Quad */
	glVertex3f(		fX+fW,  fY,		fZ);			/* Top Right */
	glVertex3f(		fX+fW,	fY+fH,	fZ);			/* Bottom Right */
	glVertex3f(		fX+fW,	fY+fH,	fZ+fD);			/* Bottom Right */
	glVertex3f(		fX+fW,  fY,		fZ+fD);			/* Top Right */
	glEnd( );
	//Top
	glBegin( GL_QUADS );							/* Draw A Quad */
	glVertex3f(		fX,		fY,		fZ);			/* Top Left */
	glVertex3f(		fX+fW,  fY,		fZ);			/* Top Right */
	glVertex3f(		fX+fW,  fY,		fZ+fD);			/* Top Right */
	glVertex3f(		fX,		fY,		fZ+fD);			/* Top Left */
	glEnd( );
	//Front
	glBegin( GL_QUADS );							/* Draw A Quad */
	glVertex3f(		fX,		fY,		fZ+fD);			/* Top Left */
	glVertex3f(		fX+fW,  fY,		fZ+fD);			/* Top Right */
	glVertex3f(		fX+fW,	fY+fH,	fZ+fD);			/* Bottom Right */
	glVertex3f(		fX,		fY+fH,	fZ+fD);			/* Bottom Left */
	glEnd( );
}

void mGraphics::draw4Verts(mVertex* a, mVertex* b, mVertex* c, mVertex* d){
	glBegin( GL_QUADS );					/* Draw A Quad */
	glColor3d(a->r, a->g, a->b);
	glVertex3f(a->x, a->y, a->z);			/* Top Left */
	glColor3d(b->r, b->g, b->b);
	glVertex3f(b->x, b->y, b->z);			/* Top Left */
	glColor3d(c->r, c->g, c->b);
	glVertex3f(c->x, c->y, c->z);			/* Top Left */
	glColor3d(d->r, d->g, d->b);
	glVertex3f(d->x, d->y, d->z);			/* Top Left */
	glEnd( );
}