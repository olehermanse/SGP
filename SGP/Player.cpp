#include "Player.h"

Player::Player(){
	keyUp = keyLeft = keyDown = keyRight = false;
	rot = 0.0f;
	radius = 500.0f;
	rot = -90.0f;
	rotOffs = 0.0f;
	acc = 0.01f;
	theta = 3*PI/2;
	phi = PI/3;
	deltaRot = 0.0f;
	pos.setSpherical(theta, phi, radius);
}

void Player::update(){
	if(pos.distance(coin->pos.x, coin->pos.y, coin->pos.z) < 100){
		coin->update();
	}
	float oldDeltaRot = deltaRot;
	
	accel = pos.getNormalized();
	mVector wz = mVector::getVector(0, 0, 1);
	accel.rotateToward(wz, 90.0f);
	mVector lz = accel;
	if(phi > PI){
		wz = mVector::getVector(0, 0, -1);
		lz = pos.getNormalized();
		lz.rotateToward(wz, 90);
	}
	accel.rotateAround(pos, rot+rotOffs);
	accel.setMagnitude(3.0f);
	if(keyUp){
		vel += accel*3;
	}else if(keyDown){
		vel *= 0.8;
	}
	
	if(keyLeft && !keyRight){
		rotOffs += 2.0f;
	}else if(!keyLeft && keyRight){
		rotOffs -= 2.0f;
	}
	
	mVector end = pos + vel;
	end.setMagnitude(500.0f);
	vel = end - pos;
	
	if(vel.length() >0.01f)
		deltaRot = vel.angleTo(lz);
	float addRot = -1*360.0f*(deltaRot-oldDeltaRot)/(2*PI);
	if(addRot > 10.0f || addRot < -10.0f)
		addRot = 0.0f;
	//rot += addRot;
	pos += vel;
	
	float newTheta = atan2f(pos.y, pos.x);
	float newPhi = acosf(pos.z/radius);
	float dTheta = theta - newTheta;
	float distPhi = phi - PI/2;
	if(distPhi < 0.0f)
		distPhi *= -1.0f;
	if(vel.length() > 0.001f && (dTheta < PI/2 && dTheta > -(PI/2))){
		float drot = (vel.length()/(500.0f*2*PI))*360.0f*vel.angleTo(lz)/(2*PI);
		if(distPhi < PI/6)
			drot = 0.0f;
		if(dTheta < 0.0f)
			drot *= -1.0f;
		if(phi > PI/2)
			drot *= -1.0f;
		rot += 4*drot;
	}else{
		rot += rotOffs;
		rotOffs = 0;
	}
	
	pos.setMagnitude(radius);
	radius = pos.length();
	phi = newPhi;
	theta = newTheta;
}

void Player::drawSpaceShip(){
	glColor3d(0.0f, 0.0f, 1.0f);
	
	float fX = (float)0;
	float fY = (float)0;
	float fZ = (float)0;
	float fW = (float)50;
	float fH = (float)50;
	float fD = (float)25;
	glTranslatef(fX,fY,fZ);
	fX = -fW/2;
	fY = -fH/2;
	//Bottom
	glColor3d(0.0f, 0.0f, 0.0f);
	glBegin( GL_QUADS );							/* Draw A Quad */
	glVertex3f(		0,		fY,		0);			/* Top Left */
	glVertex3f(		0,  fY,		0);			/* Top Right */
	glVertex3f(		fX+fW,	fY+fH,	fZ);			/* Bottom Right */
	glVertex3f(		fX,		fY+fH,	fZ);			/* Bottom Left */
	glEnd( );
	//Back
	glColor3d(1.0f, 1.0f, 0.0f);
	glBegin( GL_QUADS );							/* Draw A Quad */
	glVertex3f(		fX+fW,	fY+fH,	fZ);			/* Bottom Right */
	glVertex3f(		fX,		fY+fH,	fZ);			/* Bottom Left */
	glVertex3f(		fX,		fY+fH,	fZ+fD);			/* Bottom Left */
	glVertex3f(		fX+fW,	fY+fH,	fZ+fD);			/* Bottom Right */
	glEnd( );
	//Right
	glColor3d(0.0f, 0.0f, 1.0f);
	glBegin( GL_QUADS );							/* Draw A Quad */
	glVertex3f(		0,		fY,		0);			/* Top Left */
	glVertex3f(		fX,		fY+fH,	fZ);			/* Bottom Left */
	glVertex3f(		fX,		fY+fH,	fZ+fD);			/* Bottom Left */
	glVertex3f(		0,		fY,		0);			/* Top Left */
	glEnd( );
	//Left
	glColor3d(0.0f, 0.0f, 1.0f);
	glBegin( GL_QUADS );							/* Draw A Quad */
	glVertex3f(		0,  fY,		0);			/* Top Right */
	glVertex3f(		fX+fW,	fY+fH,	fZ);			/* Bottom Right */
	glVertex3f(		fX+fW,	fY+fH,	fZ+fD);			/* Bottom Right */
	glVertex3f(		0,  fY,		0);			/* Top Right */
	glEnd( );
//	//Front
//	glColor3d(1.0f, 0.0f, 0.0f);
//	glBegin( GL_QUADS );							/* Draw A Quad */
//	glVertex3f(		fX,		fY,		fZ);			/* Top Left */
//	glVertex3f(		fX+fW,  fY,		fZ);			/* Top Right */
//	glVertex3f(		fX+fW,  fY,		fZ+fD);			/* Top Right */
//	glVertex3f(		fX,		fY,		fZ+fD);			/* Top Left */
//	glEnd( );
	//Top
	glColor3d(0.5f, 0.5f, 1.0f);
	glBegin( GL_QUADS );							// Draw A Quad
	glVertex3f(		0,		fY,		0);			// Top Left
	glVertex3f(		0,  fY,		0);			// Top Right
	glVertex3f(		fX+fW,	fY+fH,	fZ+fD);			// Bottom Right
	glVertex3f(		fX,		fY+fH,	fZ+fD);			// Bottom Left
	glEnd( );
}

void Player::draw(){
	glPushMatrix();
	if(gfx->cameraMode == 2){
		mVector temp = pos;
		pos.setSpherical(3*PI/2, phi, radius);
		glTranslatef(pos.x+gfx->W/2, pos.y+gfx->H/2, pos.z);
		rotate();
		drawSpaceShip();
		pos = temp;
	}else{
		glTranslatef(pos.x+gfx->W/2, pos.y+gfx->H/2, pos.z);
		rotate();
		drawSpaceShip();
	}
	glPopMatrix();
}

mGraphics* Player::gfx = 0;


void Player::rotate(){
	if(gfx->cameraMode == 2){
		float yRot = 180*(phi/PI);
		glRotatef(yRot, 1, 0, 0);
		glRotatef(rot+rotOffs-180, 0,0,-1);
	}else{
		float xRot = 360*(theta/(2*PI));
		float yRot = 180*(phi/PI);
		glRotatef(xRot, 0, 0, 1);
		glRotatef(yRot, 0, 1, 0);
		glRotatef(rot+rotOffs-90, 0,0,1);
	}
	
}