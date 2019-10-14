#pragma once
#include "Headers/Object.h"

class Block : public Object
{
private:
	
public:
	Block(float x, float y) {
		objectType = 0;
		pos.x = x;
		pos.y = y;
		width = 0.12f;
		height = 0.02f;
		colour[0] = 200;
		colour[1] = 200;
		colour[2] = 200;
	}

	float getX();
	float getY();

	/*void drawBox() const;*/
	

};

