#pragma once
#include "Headers/Object.h"

class Paddle : public Object
{
private:

	b2PolygonShape dynamicShape;


public:

	Paddle() //Mostly see block constructor for comments
	{
		objectType = 1; //paddle type. Unused.
		pos.x = 0.f;
		pos.y = -0.875f;
		width = 0.15f; //half of actual width
		height = 0.02f;
		colour[0] = 200;
		colour[1] = 0;
		colour[2] = 0;
		
		bodyDef.position.Set(pos.x / 5, pos.y / 5);
		bodyDef.type = b2_dynamicBody;

		dynamicShape.SetAsBox(width / 6, height / 6); //dunno why 6

		fixtureDef.shape = &dynamicShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

	
	}
	

	void setXPos(float x);


	const b2PolygonShape getShape() {
		return dynamicShape;
	}

	

};

