#ifndef __GameJam__mHeightmap__
#define __GameJam__mHeightmap__

#include "mGraphics.h"

class mHeightmap{
public:
	const USHORT ROWS;
	const USHORT COLS;
	USHORT width;
	USHORT height;
	mHeightmap(USHORT rows, USHORT columns);
	~mHeightmap();
	void setSize(USHORT w, USHORT h);
	void setXY();
	void reset();
	void randomizeZ(USHORT range);
	void smooth();
	void setColors();
	void draw(mGraphics* gfx);
	mVertex** hmap;
	
	void wrapToSphere(float radius);
private:
	
};

#endif /* defined(__mGraphics__mHeightmap__) */
