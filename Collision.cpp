#include "Headers/Collision.h"

//Runs immediately on contact
void Collision::BeginContact(b2Contact* contact) {

	//Store current velocity
	oldVelocity = contact->GetFixtureB()->GetBody()->GetLinearVelocity();
	//Set velocity to 0, to keep each bounce consistent
	contact->GetFixtureB()->GetBody()->SetLinearVelocity(b2Vec2(0, 0));

	//Cast the void pointer back to its correct type
	objectUserData* colA = static_cast<objectUserData*>(contact->GetFixtureA()->GetBody()->GetUserData());
	objectUserData* colB = static_cast<objectUserData*>(contact->GetFixtureB()->GetBody()->GetUserData());

	//TODO
	//Make force new velocity
	//Velocity currently increases when blocks are hit
	colA->colliding = true;
	colB->colliding = true;



}

//Runs after contact stay (e.g. ball rolls off edge)
void Collision::EndContact(b2Contact* contact) { }

//Runs before physics calculations
void Collision::PreSolve(b2Contact* contact) { } 

//Runs after physics calculations
void Collision::PostSolve(b2Contact* contact) { }