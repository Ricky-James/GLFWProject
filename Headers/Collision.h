#pragma once
#include "Box2D/Box2D.h"
#include "Ball.h"
#include "Paddle.h"
#include <iostream>

class Collision : public b2ContactListener
{
private:
	b2Vec2 oldVelocity;
public:

	

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact);
	void PostSolve(b2Contact* contact);






};

