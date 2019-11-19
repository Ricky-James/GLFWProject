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

	glPointSize(4);
	
	glBegin(GL_POLYGON); //Top left, clockwise

	glVertex2f( pos.x - width / 2, pos.y + height / 2 );
	glVertex2f( pos.x + width / 2, pos.y + height / 2 );
	glVertex2f( pos.x + width / 2, pos.y - height / 2 );
	glVertex2f( pos.x - width / 2, pos.y - height / 2 );
	

	glRotatef(this->body->GetAngle(), 0, 0, 1);

	std::cout << "Paddle rotation (RADS): " << this->body->GetAngle() << std::endl;


	glEnd();
}

void Object::setName(std::string _name)
{
	assert(_name.length() > 0);
	userdata.name = _name;
}
