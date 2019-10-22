#pragma once
#include <GLFW/glfw3.h>
#include <Box2D/Box2D.h>
#include "Vector2.h"

class Object
{

	

public:



	Vector2 pos;
	float angle;
	float width;
	float height;

	float colour[3];

	b2BodyDef bodyDef;
	
	b2Body* body;
	b2FixtureDef fixtureDef;


	void drawBox(b2Vec2 pos);
};

