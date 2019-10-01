#include "Ball.h"

const void Ball::moveLeft(bool left) {
	if (left) {
		pos.x -= 0.05f;
	}
	else { return; }

}
const void Ball::moveRight(bool right) {
	if (right) {
		pos.x += 0.05f;
	}
	else { return; }
}

const void Ball::drawBall() {
	for (int i = 0; i < 360; i++) {
		float degInRad = i * DEG2RAD;
		glVertex2f(((cos(degInRad) * radius) + pos.x), ((sin(degInRad) * radius) + pos.y));
	}
}