#include "Headers/Object.h"



void Object::setColours(int r, int g, int b) //Values between 0-255
{
	assert(r >= 0, g >= 0, b >= 0);
	assert(r <= 255, g <= 255, b <= 255);

	colour[0] = r / 255.0f;
	colour[1] = g / 255.0f;
	colour[2] = b / 255.0f;

}

void Object::setColours(float r, float g, float b) //Values between 0-1
{
	assert(r >= 0, g >= 0, b >= 0);
	assert(r <= 1, g <= 1, b <= 1);

	colour[0] = r;
	colour[1] = g;
	colour[2] = b;

}

void Object::setName(std::string _name)
{
	assert(_name.length() > 0);
	userdata.name = _name;
}
