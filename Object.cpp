#include "Headers/Object.h"
#include <iostream>

#define RAD2DEG 57.2958 
#define DEG2RAD 0.0174533

//void Object::drawBox(b2Vec2 pos) {
//
//
//	glBegin(GL_QUADS); //Top left, clockwise
//	
//	//Angle still dysfunctional
//
//	Vector2 TL = { body->GetWorldCenter().x - width / 2, body->GetWorldCenter().y + height / 2 };
//	Vector2 TR = { body->GetWorldCenter().x + width / 2, body->GetWorldCenter().y + height / 2 };
//	Vector2 BR = { body->GetWorldCenter().x + width / 2, body->GetWorldCenter().y - height / 2 };
//	Vector2 BL = { body->GetWorldCenter().x - width / 2, body->GetWorldCenter().y - height / 2 };
//
//
//	glVertex2f(TL.x, TL.y);
//	glVertex2f(TR.x, TR.y);
//	glVertex2f(BR.x, BR.y);
//	glVertex2f(BL.x, BL.y);
//
//
//	glEnd();
//
//
//}

void Object::drawBox()
{
	b2Vec2 pos = this->body->GetPosition();



	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();             // save the current GL_MODELVIEW matrix 


	glBegin(GL_QUADS); //Top left, clockwise

	glTranslatef(pos.x, pos.y, 0.0f);
	glRotatef(this->body->GetAngle(), 0, 0, 1);  // rotate your object
	
	glVertex2f( pos.x - width / 2, pos.y + height / 2 );
	glVertex2f( pos.x + width / 2, pos.y + height / 2 );
	glVertex2f( pos.x + width / 2, pos.y - height / 2 );
	glVertex2f( pos.x - width / 2, pos.y - height / 2 );

	
	

	if(this->getName() == "Paddle")
		std::cout << "Rotation (RADS): " << this->body->GetAngle() << std::endl;


	glEnd();

	glPopMatrix();              // restore the GL_MODELVIEW matrix

}

void Object::setName(std::string _name)
{
	assert(_name.length() > 0);
	userdata.name = _name;
}
