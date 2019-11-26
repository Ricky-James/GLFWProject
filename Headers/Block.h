#pragma once
#include "Headers/Object.h"

class Block : public virtual Object
{
private:
	
	b2PolygonShape shape;

public:
	Block(float x, float y, float width, float height, b2BodyType type) {

		pos.x = x;
		pos.y = y;
		this->width = width;
		this->height = height;
		colour[0] = 52  / 255.0f;
		colour[1] = 204 / 255.0f;
		colour[2] = 235 / 255.0f;

		//B2D
		bodyDef.type = type; //Unaffected by gravity
		
		//Shape
		shape.SetAsBox(width / 2, height / 2);

		//Fixture

		fixtureDef.shape = &shape; //Attach shape & body
		fixtureDef.density = 0.1f;
		fixtureDef.friction = 0;
		fixtureDef.restitution = 1.0f;
		bodyDef.linearDamping = 1.0f; //Basically air resistance
		
		//body->SetUserData(&userdata);
		
		bodyDef.position = b2Vec2(x, y);

	}

	~Block()
	{
		//Increase ball speed?
		//Reduce paddle size?
		//Game state can change for every block destroyed.
	}

	void draw() override;

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

