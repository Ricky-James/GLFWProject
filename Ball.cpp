#include "Headers/Ball.h"

void Ball::moveLeft() {
	
	pos.x -= 0.05f;


}
void Ball::moveRight() {
	
	pos.x += 0.05f;
	
}

void Ball::drawBall() const {
	glBegin(GL_POLYGON);

	//glColor3f(pos.y*100, 255, pos.y*100);
	for (int i = 0; i < 360; i++) {
		float degInRad = i * DEG2RAD;
		glVertex2f(((cos(degInRad) * radius) + pos.x), ((sin(degInRad) * radius) + pos.y));
	}

	glEnd();
}