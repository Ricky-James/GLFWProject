#pragma once
#include <GLFW/glfw3.h>
#include <Box2D/Box2D.h>
#include "Vector2.h"
#include <string>

#define RAD2DEG 57.2958 
#define DEG2RAD 0.0174533

//Information used to identify objects in collisions
struct objectUserData
{
	std::string name;
	bool colliding;
};

//Abstract class for all defined objects
class Object
{
private:


protected:
	Object()
	{
		objectInfo->name = "NULL. Unknown Object Name.";
		pos.set (0, 0);
		angle = 0;
		width = 0;
		height = 0;
		setColours(0, 0, 0);
		body = NULL;
		
	}

public:



	objectUserData* objectInfo = new objectUserData();
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
	std::string getName() { return objectInfo->name; }

	virtual const Vector2 getPos()
	{
		return pos;
	}



};

