#include "Headers/Paddle.h"

void Paddle::setXPos(float x)
{
	if (x > -1 && x < 1) {
		pos.x = x;
//		bodyDef.position.Set(x, pos.y);
		body->SetTransform(b2Vec2(x, pos.y), body->GetAngle());
	}
}



