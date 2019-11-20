#pragma once
#include <GLFW/glfw3.h>
#include <Box2D/Box2D.h>
#include "Vector2.h"
#include <string>

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
	


	void drawBox();
	void setColours(int r, int g, int b);
	void setName(std::string _name);

	const std::string getName()
	{
		return userdata.name;
	}


	const Vector2 getPos()
	{
		return pos;
	}



};

