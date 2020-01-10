#include "Headers/Block.h"

void Block::draw()
{
	b2Vec2 center = body->GetPosition();
	float32 angle = body->GetAngle();

	glMatrixMode(GL_MODELVIEW);
	glColor3f(this->colour[0], this->colour[1], this->colour[2]);

	glPushMatrix();             // save the current GL_MODELVIEW matrix 
	{
		glTranslatef(center.x, center.y, 0.0f);
		glRotatef(angle * RAD2DEG, 0, 0, 1);  // rotate object
		glTranslatef(-center.x, -center.y, 0.0f);
	}


	float points[8] = {
		(center.x - width / 2), (center.y + height / 2),
		(center.x + width / 2), (center.y + height / 2),
		(center.x + width / 2), (center.y - height / 2),
		(center.x - width / 2), (center.y - height / 2)
	};

	glBegin(GL_QUADS); //Top left, clockwise
	{
		for (int i = 0; i < 8; i += 2)
		{
			glVertex2f(points[i], points[i + 1]);
		}
	}
	glEnd();

	glPopMatrix();              // restore the GL_MODELVIEW matrix
}




