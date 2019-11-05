#pragma once
#include "Headers/Object.h"

class Block : public Object
{
private:
	
	

public:
	Block(float x, float y) {

		pos.x = x;
		pos.y = y;
		width = 0.24f;
		height = 0.04f;
		colour[0] = 200;
		colour[1] = 200;
		colour[2] = 200;

		//B2D
		bodyDef.position.Set(x, y);
		bodyDef.type = b2_staticBody; //Unaffected by gravity
		
		//Shape
		shape.SetAsBox(width / 2, height / 2);

		//Fixture

		fixtureDef.shape = &shape; //Attach shape & body
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.restitution = 1.0f;
		bodyDef.linearDamping = 1.0f;
		

	}

	float getX();
	float getY();

	void setName(std::string _name, int count)
	{
		assert(_name.length() > 0);
		assert(count >= 0);
		_name.append(std::to_string(count));
		Object::setName(_name);

	}

	const b2PolygonShape getShape() {
		return shape;
	}
	
};

