#pragma once
#include "Headers/Object.h"

class Paddle : public Object
{
private:

	b2PolygonShape kinematicShape;


public:

	Paddle() //Mostly see block constructor for comments
	{
		pos.x = 0.f;
		pos.y = -0.875f;
		width = 0.15f; //half of actual width
		height = 0.02f;
		colour[0] = 200;
		colour[1] = 0;
		colour[2] = 0;
		
		bodyDef.position.Set(pos.x / 6, pos.y / 6);
		bodyDef.type = b2_kinematicBody;

		kinematicShape.SetAsBox(width / 6, height / 6);

		fixtureDef.shape = &kinematicShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

	
	}
	

	void setXPos(float x);


	const b2PolygonShape getShape() {
		return kinematicShape;
	}
	const Vector2 getPos()
	{
		return pos;
	}

	

};

