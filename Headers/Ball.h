#pragma once
#include "Headers/Object.h"
#include <GLFW/glfw3.h>
#include <math.h>

class Ball : public Object
{

private:
	

	Vector2 pos, spd;
	
	const float radius = 0.05f;
	const float DEG2RAD = 3.14159 / 180;


public:
	Ball()
	{
		pos.x = 0; pos.y = 0;
		spd.x = 0; spd.y = 0;
	}

	float getxspeed() const { return spd.x; }
	float getyspeed() const { return spd.y; }
	float getxpos()   const { return pos.x; }
	float getypos()   const { return pos.y; }

	void moveLeft();
	void moveRight();

	//Draws ball to screen (+ position)
	void drawBall() const;
	
	
};

