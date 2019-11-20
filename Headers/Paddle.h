#pragma once
#include "Headers/Object.h"

class Paddle : public Object
{
private:

	b2PolygonShape shape;
	float rotation;
	float const maxRotate = 30;

public:




	Paddle() //Mostly see block constructor for comments
	{
		setName("Paddle");
		pos.x = 0.f;
		pos.y = -0.875f;
		width = 0.3f; //half of actual width
		height = 0.04f;
		colour[0] = 0.6f;
		colour[1] = 0;
		colour[2] = 0.6f;
		
		bodyDef.position.Set(pos.x, pos.y);
		bodyDef.type = b2_kinematicBody;

		bodyDef.allowSleep = false; //Stops blocks from sleeping if they fall onto the paddle

		shape.SetAsBox(width/2, height/2);
		

		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0;
		fixtureDef.restitution = 1.0f;




	}
	
	void updateRotation();

	float getRotation(); //Sets rotation according to body xPos and returns new value
	void updatePosition(float x);
	const b2PolygonShape getShape() {
		return shape;
	}



	

};

