#pragma once
#include "Object.h"
#include <GLFW/glfw3.h>
#include <math.h>

class Ball : public Object
{

private:
	struct Vector2 {
	public:
		float x, y;
	};

	Vector2 pos, spd;
	
	const float radius = 0.05f;
	const float DEG2RAD = 3.14159 / 180;


public:
	Ball()
	{
		pos.x = 0; pos.y = 0;
		spd.x = 0; spd.y = 0;
	}

	const float getxspeed() { return spd.x; }
	const float getyspeed() { return spd.y; }
	const float getxpos() { return pos.x; }
	const float getypos() { return pos.y; }

	const void moveLeft(bool left);
	const void moveRight(bool right);

	//Draws ball to screen (+ position)
	const void drawBall();
	
	
};

