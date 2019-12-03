#include "Headers/Collision.h"

void Collision::BeginContact(b2Contact* contact) {

	//TODO
	//Set old velocity
	oldVelocity = contact->GetFixtureB()->GetBody()->GetLinearVelocity();

}

void Collision::EndContact(b2Contact* contact) {

	//check if fixture A was a ball
	void* fixAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
	void* fixBUserData = contact->GetFixtureB()->GetBody()->GetUserData();
	//std::string* objectName = static_cast<std::string*>(bodyUserData);

	Ball* ballCheck = static_cast<Ball*>(fixBUserData);
	if (ballCheck != NULL)
	{
		std::cout << "Ball check success" << std::endl;
	}
	Paddle* paddleCheck = static_cast<Paddle*>(fixAUserData);
	if (paddleCheck != NULL)
	{
		std::cout << "Paddle check success" << std::endl;
	}



	std::cout << "Collision detected" << std::endl;

	std::cout << "Ball Name: " << (ballCheck->getName()) << std::endl;
	std::cout << "Paddle Name: " << (paddleCheck->getName()) << std::endl;

	std::cout << "Fixture A: " << (contact->GetFixtureA()->GetUserData()) << std::endl;
	std::cout << "Fixture B: " << (contact->GetFixtureB()->GetUserData()) << std::endl;
	contact->GetFixtureB()->GetBody()->SetAngularVelocity(0.0f);
	//contact->GetFixtureB()->GetBody()->ApplyForce(b2Vec2(-contact->GetFixtureB()->GetBody()->GetLinearVelocity().x * 2,
	//	-contact->GetFixtureB()->GetBody()->GetLinearVelocity().y * 2),
	//	contact->GetFixtureB()->GetBody()->GetLocalCenter(), true);

	//TODO
	//Make force new velocity
	//CHECK FOR PADDLE.
	//Velocity currently increases when blocks are hit

	contact->GetFixtureB()->GetBody()->ApplyForce(-oldVelocity,
		contact->GetFixtureB()->GetBody()->GetLocalCenter(), true);

}