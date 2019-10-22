#pragma once
#include "Headers/Object.h"

class Block : public Object
{
private:
	
	b2PolygonShape dynamicShape;

public:
	Block(float x, float y) {
		pos.x = x;
		pos.y = y;
		width = 0.12f;
		height = 0.02f;
		colour[0] = 200;
		colour[1] = 200;
		colour[2] = 200;

		//B2D
		bodyDef.position.Set(x/5, y/5);
		bodyDef.type = b2_dynamicBody; //Unaffected by gravity
		
		//Shape
		dynamicShape.SetAsBox(width /6, height /6); //idk why 6 still, inaccurate body.
		//Fixture
	//	body->CreateFixture(&dynamicShape, 1.0f); //Density
		fixtureDef.shape = &dynamicShape; //Attach shape & body
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

	}

	float getX();
	float getY();
	const b2PolygonShape getShape() {
		return dynamicShape;
	}
	
};

