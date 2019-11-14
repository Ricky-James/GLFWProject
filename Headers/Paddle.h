#pragma once
#include "Headers/Object.h"

class Paddle : public Object
{
private:

	

public:

	float rotation;

	Paddle() //Mostly see block constructor for comments
	{
		setName("Paddle");
		pos.x = 0.f;
		pos.y = -0.875f;
		width = 0.3f; //half of actual width
		height = 0.04f;
		rotation = 0.0f;
		colour[0] = 200;
		colour[1] = 0;
		colour[2] = 0;
		
		bodyDef.position.Set(pos.x, pos.y);
		bodyDef.type = b2_kinematicBody;

		bodyDef.allowSleep = false; //Stops blocks from sleeping if they fall onto the paddle

		shape.SetAsBox(width/2, height/2);

		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.restitution = 10.0f;


	}
	

	void setXPos(float x);
	const b2PolygonShape getShape() {
		return shape;
	}
	const Vector2 getPos()
	{
		return pos;
	}


	

};

