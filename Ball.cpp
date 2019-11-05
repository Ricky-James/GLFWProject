#include "Headers/Ball.h"



void Ball::drawBall() const {
	glBegin(GL_POLYGON);

	glColor3f(colours[0], colours[1], colours[2]);

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

void Ball::setColours(float r, float g, float b)
{
	if (r >= 0 && r <= 1) {
		colours[0] = r;
	}
	if (g >= 0 && g <= 1) {
		colours[1] = g;
	}
	if (b >= 0 && b <= 1) {
		colours[2] = b;
	}

}
