#pragma once
#include "Headers/Object.h"
#include "Block.h"

//Quit similar to Blocks, could probably be refactored to inherit from Block
class Paddle : public virtual Object
{
private:

	b2PolygonShape shape;
	int objType;
	bool movingRight = true; //Used for spin paddle only
	const float spinSpeed = 2.0f;
public:

	Paddle() //Mostly see block constructor for comments
	{
		collided = false;
		movingRight = true;
		objType = PADDLE;
		pos.y = -0.875f;
		width = 0.3f; //half of actual width
		height = 0.04f;
		colour[0] = 0.6f;
		colour[1] = 0;
		colour[2] = 0.6f;
		
		//Body
		bodyDef.position.Set(pos.x, pos.y);
		bodyDef.type = b2_kinematicBody;
		bodyDef.allowSleep = false;

		//Shape
		shape.SetAsBox(width/2, height/2);

		//Fixture
		fixtureDef.shape = &shape;
		fixtureDef.density = 2.0f;
		fixtureDef.friction = 1.0f;
		fixtureDef.restitution = 1.0f;

	}
	~Paddle() {}

	void setObjectType(int type) {
		objType = type;
	}
	void draw() override;
	int objectType() override { return objType; }
	void SpinMove();

	
	void updatePosition(float x);
	const b2PolygonShape getShape() {
		return shape;
	}



	

};

