#include "Headers/Paddle.h"



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


