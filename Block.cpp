#include "Headers/Block.h"

void Block::setName(std::string _name, int count)
{
	assert(_name.length() > 0);
	assert(count >= 0);
	_name.append(std::to_string(count));
	Object::setName(_name);

}




