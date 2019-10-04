#pragma once
#include <GLFW/glfw3.h>


class Object
{
private:
	
public:
	
	struct Vector2 {
	public:
		float x, y;
	};

	Vector2 pos;
	float width;
	float height;

	virtual void drawBox() const;
};

