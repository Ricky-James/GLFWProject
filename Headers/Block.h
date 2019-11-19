#pragma once
#include "Headers/Object.h"

class Block : public Object
{
private:
	
	b2PolygonShape shape;

public:
	Block(float x, float y, float _width, float _height) {

		pos.x = x;
		pos.y = y;
		width = _width;
		height = _height;
		colour[0] = 200;
		colour[1] = 200;
		colour[2] = 200;

		//B2D
		//bodyDef.position.Set(x, y);
		bodyDef.type = b2_staticBody; //Unaffected by gravity
		
		//Shape
		shape.SetAsBox(width / 2, height / 2);

		//Fixture

		fixtureDef.shape = &shape; //Attach shape & body
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.restitution = 1.0f;
		bodyDef.linearDamping = 1.0f;
		
		bodyDef.position = b2Vec2(x, y);

	}

	~Block()
	{
		//Increase ball speed?
		//Reduce paddle size?
		//Game state can change for every block destroyed.
	}
	void hit()
	{
		//Changing body type causes it to be affected by gravity and fall
		bodyDef.type = b2_dynamicBody;
	}

	void setName(std::string _name, int count);

	const b2PolygonShape getShape() {
		return shape;
	}
	
	
};

