#include "Headers/Block.h"

void Block::draw()
{

	b2Vec2 center = this->body->GetPosition();
	float32 angle = this->body->GetAngle();

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

void Block::setName(std::string _name, int count)
{
	assert(_name.length() > 0);
	assert(count >= 0);
	_name.append(std::to_string(count));
	Object::setName(_name); //Sets name with new appended name

}




