#include "mHeightmap.h"

mHeightmap::mHeightmap(USHORT rows, USHORT columns):
ROWS(rows),
COLS(columns){
	hmap = (mVertex**)malloc(sizeof(mVertex*)*rows);
	for(int i = 0; i<rows; ++i){
		hmap[i] = (mVertex*)malloc(sizeof(mVertex)*columns);
	}
	assert(hmap);
}
mHeightmap::~mHeightmap(){
	for(int i = 0; i<ROWS; ++i){
		free(hmap[i]);
	}
	free(hmap);
}

void mHeightmap::setSize(USHORT w, USHORT h){
	width = w;
	height = h;
	reset();
}

void mHeightmap::setXY(){
	float indW = (float)width/(float)COLS;
	float indH = (float)height/(float)ROWS;
	for(int i = 0; i<ROWS; ++i){
		for(int j = 0; j<COLS; ++j){
			hmap[i][j].x = (float)j*indW;
			hmap[i][j].y = (float)i*indH;
		}
	}
}

void mHeightmap::reset(){
	setXY();
	for(int i = 0; i<ROWS; ++i){
		for(int j = 0; j<COLS; ++j){
			hmap[i][j].z = 0.0f;
			hmap[i][j].r = hmap[i][j].g = hmap[i][j].b = 1.0f;
		}
	}
}

void mHeightmap::draw(mGraphics* gfx){
	glPushMatrix();
	glTranslatef(gfx->W/2, gfx->H/2, 0);
	for(int i = 0; i<ROWS-1; ++i){
		for(int j = 0; j<COLS-1; ++j){
			gfx->draw4Verts(&hmap[i][j], &hmap[i+1][j], &hmap[i+1][j+1], &hmap[i][j+1]);
		}
	}
	glPopMatrix();
}
void mHeightmap::randomizeZ(USHORT range){
	float fRange = (float)range;
	float fRandom = 0;
	int ign = 4;
	for(int i = ign; i<ROWS-ign; ++i){
		for(int j = 0; j<COLS; ++j){
			fRandom = rand()%range;
			if(i == 0 || i == ROWS-1)
				fRandom = fRange/2;
			hmap[i][j].z = fRandom - fRange/2;
			hmap[i][j].r = (float)fRandom/fRange;
			hmap[i][j].g = (float)fRandom/fRange;
		}
	}
	int r1;
	int r2;
	int r3;
	int r4;
	for(int i = 0; i<10; ++i){
		r1 = rand()%(ROWS - 2*ign) + ign;
		r2 = rand()%(COLS);;
		r3 = rand()%2;
		r4 = rand()%100;
		if(r3)
			r4 = -r4;
		hmap[r1][r2].z += r4;
	}
}

void mHeightmap::smooth(){
	float sum;
	float cnt;
	float avg;
	float newMap[ROWS][COLS];
	for(int i = 0; i < ROWS; ++i){
		for(int j = 0; j < COLS; ++j){
			sum = 0.0f;
			cnt = 0.0f;
			if(i!=0){
				if(j!=0){
					sum += hmap[i-1][j-1].z;
					cnt += 1.0f;
				}
				if(j != COLS-1){
					sum += hmap[i-1][j+1].z;
					cnt += 1.0f;
				}
				sum += hmap[i-1][j].z;
				cnt += 1.0f;
			}
			if(i != ROWS-1){
				if(j!=0){
					sum += hmap[i+1][j-1].z;
					cnt += 1.0f;
				}
				if(j != COLS-1){
					sum += hmap[i+1][j+1].z;
					cnt += 1.0f;
				}
				sum += hmap[i+1][j].z;
				cnt += 1.0f;
			}
			if(j != 0){
				sum += hmap[i][j-1].z;
				cnt += 1.0f;
			}
			if(j != COLS-1){
				sum += hmap[i][j+1].z;
				cnt += 1.0f;
			}
			avg = sum/cnt;
			newMap[i][j] = (avg+hmap[i][j].z)/2.0f;
		}
	}
	
	for(int i = 0; i < ROWS; ++i){
		for(int j = 0; j < COLS; ++j){
			hmap[i][j].z = newMap[i][j];
		}
	}
}

void mHeightmap::setColors(){
	float zMax = 0.0;
	float zMin = 0.0;
	for(int i = 0; i<ROWS; ++i){
		for(int j = 0; j<COLS; ++j){
			if(hmap[i][j].z > zMax){
				zMax = hmap[i][j].z;
			}
			if(hmap[i][j].z < zMin){
				zMin = hmap[i][j].z;
			}
			
		}
	}
	float zRange = (zMax - zMin)*0.8f;
	for(int i = 0; i<ROWS; ++i){
		for(int j = 0; j<COLS; ++j){
			hmap[i][j].r = 0.6f + hmap[i][j].z/zRange;
			hmap[i][j].g = 0.4f + hmap[i][j].z/zRange;
			hmap[i][j].b = 0.4f + hmap[i][j].z/zRange;
		}
	}
	
}
void mHeightmap::wrapToSphere(float radius){
	for(int i=0;i<ROWS; ++i){
		for(int j=0;j<COLS-1; ++j){
			if(i == 0 || i == ROWS-1){
				//TODO MAKE BETTER
				hmap[i][j] = hmap[i][j].convert2DToSphere(radius, width, height);
				hmap[i][j].x = 0.0f;
				hmap[i][j].y = 0.0f;
			}else{
				hmap[i][j] = hmap[i][j].convert2DToSphere(radius+hmap[i][j].z, width, height);
			}
		}
	}
	int j = COLS-1;
	for(int i=0;i<ROWS; ++i){
		if(j == COLS-1){
			hmap[i][j] = hmap[i][0];
		}
	}
	
}
