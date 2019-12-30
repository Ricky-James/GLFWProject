#pragma once
#include <GLFW/glfw3.h>
#include <Box2D/Box2D.h>
#include "Vector2.h"
#include <string>

#define RAD2DEG 57.2958 
#define DEG2RAD 0.0174533
#define BALL 1
#define PADDLE 2
#define BLOCK 3
#define WALL 4


//Class for all defined objects
//Class CANNOT be abstract as collisions need to to be dereferenced as objects
class Object
{
private:


protected:
	Object()
	{
		pos.set (0, 0);
		width = 0;
		height = 0;
		setColours(0, 0, 0);
		body = NULL;
		
	}

public:

	
	Vector2 pos;

	float width;
	float height;
	GLfloat colour[3];

	b2BodyDef bodyDef;
	
	b2Body* body;
	b2FixtureDef fixtureDef;
	
	virtual void draw() = 0;
	void setColours(int r, int g, int b); //For values 0-255, converts to 0-1
	void setColours(float r, float g, float b); //For values 0-1

	//Ball 1, Paddle 2, Block 3, Wall 4
	virtual int objectType() = 0;

	virtual const Vector2 getPos()
	{
		return pos;
	}



};

