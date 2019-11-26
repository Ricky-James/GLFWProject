#pragma once
#include <GLFW/glfw3.h>
#include <Box2D/Box2D.h>
#include "Vector2.h"
#include <string>

#define RAD2DEG 57.2958 
#define DEG2RAD 0.0174533

//Abstract class for all defined objects
class Object
{
private:
	struct Userdata {
		std::string name;
	};


public:

	Userdata userdata;

	Vector2 pos;
	float angle;
	float width;
	float height;
	GLfloat colour[3];

	b2BodyDef bodyDef;
	
	b2Body* body;
	b2FixtureDef fixtureDef;
	
	virtual void draw() = 0;
	void setColours(int r, int g, int b); //For values 0-255, converts to 0-1
	void setColours(float r, float g, float b); //For values 0-1
	void setName(std::string _name);

	virtual const std::string getName()
	{
		return userdata.name;
	}


	virtual const Vector2 getPos()
	{
		return pos;
	}



};

