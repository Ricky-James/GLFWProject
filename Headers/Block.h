#pragma once
#include "Headers/Object.h"

class Block : public Object
{
private:
	
	b2PolygonShape kinematicShape;

public:
	Block(float x, float y) {
		objectType = 0;
		pos.x = x;
		pos.y = y;
		width = 0.12f;
		height = 0.02f;
		colour[0] = 200;
		colour[1] = 200;
		colour[2] = 200;

		//B2D
		bodyDef.position.Set(x/5, y/5);
		bodyDef.type = b2_kinematicBody; //Unaffected by gravity
		
		//Shape
		kinematicShape.SetAsBox((width / 2)/5, (height / 2)/5);
		//Fixture
	//	body->CreateFixture(&dynamicShape, 1.0f); //Density
		fixtureDef.shape = &kinematicShape; //Attach shape & body
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;

	}

	float getX();
	float getY();
	b2PolygonShape getShape() {
		return kinematicShape;
	}
	
};

