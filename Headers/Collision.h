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

	void BeginContact(b2Contact* contact) override;
	void EndContact(b2Contact* contact) override;
	void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;
	void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

};

