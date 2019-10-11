#pragma once
#include <GLFW/glfw3.h>


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

	void drawBox() const;
};

