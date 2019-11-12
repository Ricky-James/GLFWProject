#include "Headers/Object.h"


void Object::drawBox(b2Vec2 pos) {


	glBegin(GL_QUADS); //Top left, clockwise
	
	//Angle still dysfunctional
	glRotatef(45, pos.x, pos.y, 0); 
	

	Vector2 TL = { body->GetPosition().x - width / 2, body->GetPosition().y + height / 2 };
	Vector2 TR = { body->GetPosition().x + width / 2, body->GetPosition().y + height / 2 };
	Vector2 BR = { body->GetPosition().x + width / 2, body->GetPosition().y - height / 2 };
	Vector2 BL = { body->GetPosition().x - width / 2, body->GetPosition().y - height / 2 };


	glVertex2f(TL.x, TL.y);
	glVertex2f(TR.x, TR.y);
	glVertex2f(BR.x, BR.y);
	glVertex2f(BL.x, BL.y);


	glEnd();


}

void Object::setName(std::string _name)
{
	assert(_name.length() > 0);
	name = _name;
}
