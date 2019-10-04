#pragma once
#include "Headers/Object.h"

class Block : public Object
{
private:
	
public:
	Block(float x, float y) {
		pos.x = x;
		pos.y = y;
		width = 0.1f;
		height = 0.02f;
		
	}


};

