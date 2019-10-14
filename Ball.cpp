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