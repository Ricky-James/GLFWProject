#include "Headers/Object.h"


void Object::drawBox() const {
	//Calculate verts
	Vector2 TL = { pos.x - width, pos.y + height };
	Vector2 TR = { pos.x + width, pos.y + height };
	Vector2 BR = { pos.x + width, pos.y - height };
	Vector2 BL = { pos.x - width, pos.y - height };


	glBegin(GL_QUADS); //Top left, clockwise

	glVertex2f(TL.x, TL.y);
	glVertex2f(TR.x, TR.y);
	glVertex2f(BR.x, BR.y);
	glVertex2f(BL.x, BL.y);


	if (objectType == 0)
	{
		glColor3f(200, 0, 0);

	}
	else {
		glColor3f(255, 255, 255);
	}



	glEnd();


}