#include "Headers/Paddle.h"

void Paddle::drawPaddle() const {
	//Calculate verts
	Vector2 TL = { pos.x - paddleWidth, pos.y + paddleHeight };
	Vector2 TR = { pos.x + paddleWidth, pos.y + paddleHeight };
	Vector2 BR = { pos.x + paddleWidth, pos.y - paddleHeight };
	Vector2 BL = { pos.x - paddleWidth, pos.y - paddleHeight };


	glBegin(GL_QUADS); //Top left, clockwise

	glVertex2f(TL.x, TL.y);
	glVertex2f(TR.x, TR.y);
	glVertex2f(BR.x, BR.y);
	glVertex2f(BL.x, BL.y);

	glEnd();
	

}

Paddle Paddle::operator++(const int x) 
{
	//Overload moves paddle right
	if ((pos.x + paddleWidth) < 1) {
		pos.x += paddleSpeed;
	}
	return Paddle();
}

Paddle Paddle::operator--(const int x)
{
	//Overload moves paddle left
	if ((pos.x - paddleWidth) > -1) {
		pos.x -= paddleSpeed;
	}
	return Paddle();
}


