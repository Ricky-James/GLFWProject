#include "Headers/Block.h"

float Block::getX() { return pos.x; }

float Block::getY() { return pos.y; }

void Block::drawBox() const
{
	Object::drawBox();
}


