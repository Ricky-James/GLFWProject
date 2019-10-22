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
		width = 0.24f;
		height = 0.04f;
		colour[0] = 200;
		colour[1] = 200;
		colour[2] = 200;

		//B2D
		bodyDef.position.Set(x, y);
		bodyDef.type = b2_dynamicBody; //Unaffected by gravity
		
		//Shape
		dynamicShape.SetAsBox(width / 2, height / 2);
		//Fixture

		fixtureDef.shape = &dynamicShape; //Attach shape & body
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.restitution = 1.0f;
		

	}

	float getX();
	float getY();
	const b2PolygonShape getShape() {
		return dynamicShape;
	}
	
};

