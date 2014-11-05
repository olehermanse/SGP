#include "Coin.h"

Coin::Coin(){
	radius = 500.0f;
	update();
}

void Coin::update(){
	theta = PI + myRandom(0,PI);
	phi = myRandom(0, PI/2);
	pos.setSpherical(theta, phi, radius);
}

void Coin::draw(){
	glColor3d(1.0f, 1.0f, 0.0f);
	glPushMatrix();
	if(gfx->cameraMode == 2){
		mVector temp = pos;
		pos.setSpherical(3*PI/2, phi, radius);
		glTranslatef(pos.x+gfx->W/2, pos.y+gfx->H/2, pos.z);
		rotate();
		gfx->drawCube(0.0f, 0.0f, 0.0f, 50, 50, 50);
		pos = temp;
	}else{
		glTranslatef(pos.x+gfx->W/2, pos.y+gfx->H/2, pos.z);
		rotate();
		gfx->drawCube(0.0f, 0.0f, 0.0f, 50, 50, 50);
	}
	glPopMatrix();
}

mGraphics* Coin::gfx = 0;

void Coin::rotate(){
	if(gfx->cameraMode == 2){
		float yRot = 180*(phi/PI);
		glRotatef(yRot, 1, 0, 0);
	}else{
		float xRot = 360*(theta/(2*PI));
		float yRot = 180*(phi/PI);
		glRotatef(xRot, 0, 0, 1);
		glRotatef(yRot, 0, 1, 0);
	}
}