#include "Ball.h"

const void Ball::moveLeft() {
	
	pos.x -= 0.05f;


}
const void Ball::moveRight() {
	
	pos.x += 0.05f;
	
}

const void Ball::drawBall() {
	for (int i = 0; i < 360; i++) {
		float degInRad = i * DEG2RAD;
		glVertex2f(((cos(degInRad) * radius) + pos.x), ((sin(degInRad) * radius) + pos.y));
	}
}