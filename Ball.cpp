#include "Headers/Ball.h"



void Ball::draw() {
	glBegin(GL_POLYGON);

	glColor3f(colour[0], colour[1], colour[2]);

	for (int i = 0; i < 360; i++) {
		float degInRad = i * DEG2RAD;
		glVertex2f(((cos(degInRad) * radius) + pos.x), ((sin(degInRad) * radius) + pos.y));
	}

	glEnd();
}

void Ball::setPos(b2Vec2 b2pos)
{
	//TODO: Set >-1 <1 checks/collision
	pos.x = b2pos.x;
	pos.y = b2pos.y;
}

const b2CircleShape Ball::getShape() {
	return circleShape;
}

void Ball::ballToPaddle(b2Vec2 force)
{
	body->ApplyForce(force, body->GetPosition(), true);
}


