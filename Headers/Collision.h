#pragma once
#include "Box2D/Box2D.h"
#include "Object.h"
#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include <iostream>

class Collision : public b2ContactListener
{
public:

	void BeginContact(b2Contact* contact);
	void EndContact(b2Contact* contact);
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);



};

