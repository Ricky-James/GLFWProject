#pragma once
#include "Box2D/Box2D.h"
#include "Ball.h"
#include <iostream>

class Collision :
	public b2ContactListener
{

	void BeginContact(b2Contact* contact) {

		//check if fixture A was a ball
		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		if (bodyUserData)
			static_cast<Ball*>(bodyUserData)->startContact();

		//check if fixture B was a ball
		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserData)
			static_cast<Ball*>(bodyUserData)->startContact();
		
		std::cout << "Collision detected" << std::endl;

		std::cout << "Fixturee A: " << (contact->GetFixtureA()->GetUserData()) << std::endl;
		std::cout << "Fixturee B: " << (contact->GetFixtureB()->GetUserData()) << std::endl;
		contact->GetFixtureB()->GetBody()->ApplyForce(b2Vec2(0.0f, 3.0f),
			contact->GetFixtureB()->GetBody()->GetLocalCenter(), true);
	}

	void EndContact(b2Contact* contact) {

		//check if fixture A was a ball
		void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		if (bodyUserData)
			static_cast<Ball*>(bodyUserData)->endContact();

		//check if fixture B was a ball
		bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
		if (bodyUserData)
			static_cast<Ball*>(bodyUserData)->endContact();

	}

};

