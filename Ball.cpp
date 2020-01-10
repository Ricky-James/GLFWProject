#include "Headers/Ball.h"

void Ball::draw() {
	glBegin(GL_POLYGON);

	glColor3f(colour[0], colour[1], colour[2]);
	
	for (int i = 0; i < 360; i += 10) {
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

void Ball::paddleCollision(Paddle *paddle)
{
	//Calculate force
	float xVelocity = this->body->GetPosition().x - paddle->body->GetPosition().x;
	xVelocity *= 5;

	//Opposite to current velocity (downward) with a small multiplier and flat rate
	float yVelocity = this->body->GetLinearVelocity().y * -1.2f + 2;

	this->body->ApplyForce(b2Vec2(xVelocity, yVelocity), paddle->body->GetPosition(), true);
	collided = false;
}

const b2CircleShape Ball::getShape() {
	return circleShape;
}

void Ball::resetPos()
{
	//Easy to implement a life system here
	//No current system to display it so leaving it out for now
	this->body->SetLinearVelocity(b2Vec2_zero);
	this->body->SetTransform(b2Vec2_zero, 0);
}





