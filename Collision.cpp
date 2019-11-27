#include "Headers/Collision.h"

void Collision::BeginContact(b2Contact* contact) {

	//TODO
	//Set old velocity

}

void Collision::EndContact(b2Contact* contact) {

	//check if fixture A was a ball
	void* bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	std::string* objectName = static_cast<std::string*>(bodyUserData);



	std::cout << "Collision detected" << std::endl;
	std::cout << "Object Name: " << *objectName << std::endl;
	std::cout << "Fixture A: " << (contact->GetFixtureA()->GetUserData()) << std::endl;
	std::cout << "Fixture B: " << (contact->GetFixtureB()->GetUserData()) << std::endl;
	contact->GetFixtureB()->GetBody()->SetAngularVelocity(0.0f);
	contact->GetFixtureB()->GetBody()->ApplyForce(b2Vec2(-contact->GetFixtureB()->GetBody()->GetLinearVelocity().x * 2, -contact->GetFixtureB()->GetBody()->GetLinearVelocity().y * 2),
		contact->GetFixtureB()->GetBody()->GetLocalCenter(), true);

	//TODO
	//Make force new velocity

}