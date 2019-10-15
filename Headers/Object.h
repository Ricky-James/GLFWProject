#pragma once
#include <GLFW/glfw3.h>
#include <Box2D/Box2D.h>


class Object
{

	

public:
	
	struct Vector2 {
	public:
		float x, y;
	};

	//0 = Destroyable
	//1 = Paddle
	int objectType;
	Vector2 pos;
	float width;
	float height;

	float colour[3];

	b2BodyDef bodyDef;
	b2PolygonShape dynamicShape;
	b2Body* body;
	b2FixtureDef fixtureDef;


	void drawBox() const;
};

