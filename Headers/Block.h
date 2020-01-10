#pragma once
#include "Headers/Object.h"


class Block : public virtual Object
{
private:
	
	b2PolygonShape shape;

public:


	Block(float x, float y, float width, float height, b2BodyType bodyType) {
		
		collided = false;
		typeNumber = BLOCK;

		pos.x = x;
		pos.y = y;
		this->width = width;
		this->height = height;
		colour[0] = 52  / 255.0f;
		colour[1] = 204 / 255.0f;
		colour[2] = 235 / 255.0f;

		///Box2D
		//Shape
		shape.SetAsBox(width / 2, height / 2);

		//Fixture
		fixtureDef.shape = &shape; //Attach shape & body
		fixtureDef.density = 0.3f;
		fixtureDef.friction = 0;
		fixtureDef.restitution = 1.0f;

		//Body
		bodyDef.type = b2_staticBody; //Unaffected by physics (changed when hit)
		bodyDef.linearDamping = 3.0f; //Basically air resistance
		bodyDef.angularDamping = 0.8f;
		bodyDef.position = b2Vec2(x, y);


	}

	~Block()
	{		
		//Increase ball speed?
		//Reduce paddle size?
		//Game state can change for every block destroyed.
	}

	bool isCollided() { return collided; }
	int typeNumber;
	void draw() override;
	int objectType() override { return typeNumber; }


	const b2PolygonShape getShape() {
		return shape;
	}




	
	
};

