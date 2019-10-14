#pragma once
#include "Headers/Object.h"

class Paddle : public Object
{
private:
	const float speed = 0.03f;

public:

	Paddle()
	{
		objectType = 1;
		pos.x = 0.f;
		pos.y = -0.875f;
		width = 0.15f;
		height = 0.02f;

		
	}

	void setXPos(float x);
	Paddle operator++(const int x);
	Paddle operator--(const int x);

};

