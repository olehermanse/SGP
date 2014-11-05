#ifndef __GameJam__mPrimitives__
#define __GameJam__mPrimitives__

#include "definitions.h"

class mVector{
public:
	float x;
	float y;
	float z;
	
	mVector(){
		x = y = z = 0.0f;
	}
	
	void set(float x, float y, float z){
		(*this).x = x;
		(*this).y = y;
		(*this).z = z;
	}
	
	static mVector getVector(float x, float y, float z){
		mVector ret;
		ret.set(x,y,z);
		return ret;
	}
	
	float angleTo(mVector& ref){
		float dp = dotProduct(ref);
		float la = length();
		float lb = ref.length();
		
		return acosf(dp/(la*lb));
	}
	
	static mVector getSpherical(float theta, float phi, float r){
		mVector result;
		result.x = r * sin(phi)*cos(theta);
		result.y = r * sin(phi)*sin(theta);
		result.z = r * cos(phi);
		
		return result;
	}
	
	float distance(float fx, float fy, float fz){
		float a = fx - x;
		float b = fy - y;
		float c = fz - z;
		return sqrtf(a*a + b*b + c*c);
	}
	
	void rotateToward(mVector target, float deg){
		mVector around = target * (*this);
		rotateAround(around, -1.0f*deg);
	}
	
	void rotateAround(mVector target, float deg){
		target.normalize();
		mVector result;
		float angle = (2.0f*PI*deg)/360.0f;
		float resSine = sin(angle);
		float resCos = cos(angle);
		
		#define u target.x
		#define v target.y
		#define w target.z
		#define s resSine
		#define c resCos
		
		float part = (u*x+v*y+w*z)*(1-c);
		result.x = u*part + x*c+(v*z-w*y)*s;
		result.y = v*part + y*c+(w*x-u*z)*s;
		result.z = w*part + z*c+(u*y-v*x)*s;
		
		#undef s
		#undef c
		#undef u
		#undef v
		#undef w
		
		(*this) = result;
	}
	
	void setSpherical(float theta, float phi, float r){
		*this = getSpherical(theta, phi, r);
	}
	
	float length(){
		return sqrtf(x*x + y*y + z*z);
	}
	
	float magnitude(){
		return length();
	}
	
	void setMagnitude(float mag){
		normalize();
		*this = *this * mag;
	}
	
	void setMagnitude(mVector &ref){
		setMagnitude(ref.length());
	}
	
	void setDirection(mVector dir){
		float len = length();
		dir.normalize();
		*this = dir * len;
	}
	
	void setDirection(float x, float y, float z){
		mVector dir;
		dir.set(x,y,z);
		setDirection(dir);
	}
	
	mVector getNormalized(){
		mVector ret = *this;
		ret.normalize();
		return ret;
	}
	
	void normalize(){
		float len = length();
		if(len == 0.0f){
			return;
		}
		x = x/len;
		y = y/len;
		z = z/len;
	}
	
	void print(bool withLength=true){
		printf("(%f,%f,%f)",x,y,z);
		if(withLength)
			printf(":%f", length());
		printf("\n");
	}
	
	// Used for converting heighmap (or any 2d map) to spherical coords
	mVector convert2DToSphere(float r, float xMax, float yMax){
		float theta = (x / xMax) * 2.0f * PI;
		float phi =   PI - (y / yMax) * 1.0f * PI;
		mVector result = getSpherical(theta, phi, r);
		return result;
	}
	
	// Vector Operations:
	
	float dotProduct(const mVector &ref){
		return x*ref.x + y*ref.y + z*ref.z;
	}
	
	mVector& operator=(const mVector &ref){
		x = ref.x;
		y = ref.y;
		z = ref.z;
		return *(this);
	}
	
	mVector operator+(const mVector &ref){
		mVector ret;
		ret.x = x + ref.x;
		ret.y = y + ref.y;
		ret.z = z + ref.z;
		return ret;
	}
	
	mVector operator-(const mVector &ref){
		mVector ret;
		ret.x = x - ref.x;
		ret.y = y - ref.y;
		ret.z = z - ref.z;
		return ret;
	}
	
	mVector& operator+=(const mVector &ref){
		x += ref.x;
		y += ref.y;
		z += ref.z;
		return *this;
	}
	
	mVector& operator-=(const mVector &ref){
		x -= ref.x;
		y -= ref.y;
		z -= ref.z;
		return *this;
	}
	
	mVector operator*(const mVector &ref){
		mVector ret;
		ret.x = y*ref.z - z*ref.y;
		ret.y = z*ref.x - x*ref.z;
		ret.z = x*ref.y - y*ref.x;
		return ret;
	}
	
	mVector& operator*=(const mVector &ref){
		mVector ret = *this * ref;
		x = ret.x;
		y = ret.y;
		z = ret.z;
		return *this;
	}
	
	mVector operator*(const float &ref){
		mVector ret;
		ret.x = x*ref;
		ret.y = y*ref;
		ret.z = z*ref;
		return ret;
	}
	
	mVector& operator*=(const float &ref){
		x *= ref;
		y *= ref;
		z *= ref;
		return *this;
	}
	
	// Undefined behavior for vector division, print error and exit
	mVector operator/(const mVector &ref){
		mVector ret;
		printf("DONT DO THIS: mVector / mVector\n");
		exit(1);
		return ret;
	}
	
	
	mVector& operator/=(const mVector &ref){
		printf("DONT DO THIS: mVector /= mVector\n");
		exit(1);
		return *this;
	}
};

class mVertex: public mVector{
public:
	float r;
	float g;
	float b;
	mVertex(){
		r = g = b = 0.0f;
	}
	const mVertex& operator=(const mVector& ref){
		x = ref.x;
		y = ref.y;
		z = ref.z;
		return *this;
	}
};

#endif /* defined(__GameJam__mPrimitives__) */
