#include "Paddle.h"

const void Paddle::drawPaddle()
{

	glBegin(GL_QUADS); //Top left, clockwise

	glVertex2f(-0.1f, -0.85f);
	glVertex2f(0.1f, -0.85f);
	glVertex2f(0.1f, -0.9f);
	glVertex2f(-0.1f, -0.9f);

	glEnd();
	

}