#include "Headers/Object.h"

void Object::drawBox() const
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

void Object::setColours(int r, int g, int b) //Values between 0-255
{
	assert(r >= 0, g >= 0, b >= 0);
	assert(r <= 255, g <= 255, b <= 255);

	colour[0] = r / 255.0f;
	colour[1] = g / 255.0f;
	colour[2] = b / 255.0f;

}

void Object::setName(std::string _name)
{
	assert(_name.length() > 0);
	userdata.name = _name;
}
