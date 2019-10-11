#include "Headers/Paddle.h"



void Paddle::setXPos(float x)
{
	if (x > -1 && x < 1) {
		pos.x = x;
	}
}

Paddle Paddle::operator++(const int x)
{
	//Overload moves paddle right
	if ((pos.x + width) < 1) {
		pos.x += speed;
	}
	return Paddle();
}

Paddle Paddle::operator--(const int x)
{
	//Overload moves paddle left
	if ((pos.x - width) > -1) {
		pos.x -= speed;
	}
	return Paddle();
}


