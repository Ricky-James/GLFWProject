#pragma once
#include "Headers/Object.h"

class Paddle : public Object
{
private:
	const float speed = 0.03f;

	b2BodyDef bdef;


public:

	Paddle()
	{
		objectType = 1;
		pos.x = 0.f;
		pos.y = -0.875f;
		width = 0.15f;
		height = 0.02f;
		colour[0] = 200;
		colour[1] = 0;
		colour[2] = 0;
		
	}
	

	void setXPos(float x);
	Paddle operator++(const int x);
	Paddle operator--(const int x);

	

};

