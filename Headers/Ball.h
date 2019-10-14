#pragma once
#include <GLFW/glfw3.h>
#include <math.h>

class Ball 
{

private:
	
	struct Vector2 {
		float x, y;
	};

	Vector2 pos, spd;
	
	const float radius = 0.05f;
	const float DEG2RAD = 3.14159 / 180;

	float colours[3];

public:
	Ball()
	{
		pos.x = 0; pos.y = 0;
		spd.x = 0; spd.y = 0;
		colours[0] = 255;
		colours[1] = 255;
		colours[2] = 255;
	}

	float getxspeed() const { return spd.x; }
	float getyspeed() const { return spd.y; }
	float getxpos()   const { return pos.x; }
	float getypos()   const { return pos.y; }

	//Draws ball to screen (+ position)
	void drawBall() const;

	void setColours(float r, float g, float b)
	{
		if (r >= 0 && r <= 1) {
			colours[0] = r;
		}
		if (g >= 0 && g <= 1) {
			colours[1] = g;
		}
		if (b >= 0 && b <= 1) {
			colours[2] = b;
		}

	}
	
	
};

