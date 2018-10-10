#pragma once


class Parameter
{

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