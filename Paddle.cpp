#include "Headers/Paddle.h"

void Paddle::setXPos(float x)
{
	if (x > -1 && x < 1) {
		pos.x = x;
		body->SetTransform(b2Vec2(x, pos.y), rotation);
	}
}




