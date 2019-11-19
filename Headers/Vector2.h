#pragma once

struct Vector2 {
public:
	float x, y;

	void set(float x, float y) {
		this->x = x;
		this->y = y;
	}

	void set(Vector2 xy)
	{
		x = xy.x;
		y = xy.y;
	}

};