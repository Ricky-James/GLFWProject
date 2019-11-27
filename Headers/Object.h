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
	
protected:
	

public:

	std::string* name;
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
	virtual void setName(std::string _name);
	std::string getName() { return *name; }

	virtual const Vector2 getPos()
	{
		return pos;
	}



};

