#include "Headers/Object.h"
#include <iostream>

#define RAD2DEG 57.2958 
#define DEG2RAD 0.0174533

void Object::drawBox()
{



	b2Vec2 center = this->body->GetPosition();
	float32 angle = this->body->GetAngle();



	glMatrixMode(GL_MODELVIEW);


	glPushMatrix();             // save the current GL_MODELVIEW matrix 
	{
		glTranslatef(center.x, center.y, 0.0f);
		glRotatef(angle, 0, 0, 1);  // rotate object
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
	
	
	
	
	
	
	//glVertex2f( pos.x - width / 2, pos.y + height / 2 );
	//glVertex2f( pos.x + width / 2, pos.y + height / 2 );
	//glVertex2f( pos.x + width / 2, pos.y - height / 2 );
	//glVertex2f( pos.x - width / 2, pos.y - height / 2 );

	

	if(this->getName() == "Paddle")
		std::cout << "Rotation (RADS): " << this->body->GetAngle() << std::endl;

	if (this->getName() == "Paddle")
		std::cout << "Points[0].x: " << points[0] << std::endl;

	



}

void Object::setName(std::string _name)
{
	assert(_name.length() > 0);
	userdata.name = _name;
}
