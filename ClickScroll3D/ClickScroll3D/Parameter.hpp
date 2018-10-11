#pragma once
#define _POINTER_RELEASE(p) { if(p!=NULL) { delete p; p=NULL; } }
#define _MODEL_RELEASE(p) { if(p!=-1) { MV1DeleteModel(p); p=-1; } }
#define _VECTOR_RELEASE(p) { p.clear(); p.shrink_to_fit(); }


class Parameter
{
public:
	static const int modelNum = 3;
};

class Vector2
{
public:
	Vector2() : x(), y() {};
	Vector2(float x, float y) : x(x), y(y) {};
	~Vector2() {};

	float x;
	float y;
};