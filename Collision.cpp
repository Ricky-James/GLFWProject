#include "Headers/Collision.h"

//Runs immediately on contact
void Collision::BeginContact(b2Contact* contact) {

	//Cast the void pointer back to its correct type

	void* objectA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* objectB = contact->GetFixtureB()->GetBody()->GetUserData();

		
	//Ball cast temporarily used to determine object type
	Ball* objA = static_cast<Ball*>(objectA);
	Ball* objB = static_cast<Ball*>(objectB);

	//Pointers created to be set to outside of switch scope
	Ball* ball = nullptr;
	Paddle* paddle = nullptr;
	Block* block = nullptr;
	Block* wall = nullptr;
	//Debug assistance
	//std::cout << "Object A Type: " << objA->objectType() << std::endl;
	//std::cout << "Object B Type: " << objB->objectType() << std::endl;
	//Cast object A to its actual type
	switch (objA->objectType())
	{ 
	case 1:
		ball = static_cast<Ball*>(objectA);
		break;
	case 2: 
		paddle = static_cast<Paddle*>(objectA);
		break;
	case 3: 
		block = static_cast<Block*>(objectA);
		break;
	case 4: 
		wall = static_cast<Block*>(objectA);
		break;
	}
	//Cast object B
	switch (objB->objectType())
	{
	case 1:
		ball = static_cast<Ball*>(objectB);
		break;
	case 2:
		paddle = static_cast<Paddle*>(objectB);
		break;
	case 3: 
		block = static_cast<Block*>(objectB);
		break;
	case 4: 
		wall = static_cast<Block*>(objectB);
		break;
	}



	//If ball or a block collide with a block
	if (ball && block || objA->objectType() == BLOCK && objB->objectType() == BLOCK)
	{
		block->collision();

	}

	if (ball && paddle)
	{
		ball->hasCollided = true;
	}



	/*if (objA->objectType() == BALL && objB->objectType() == PADDLE ||
		objB->objectType() == PADDLE && objB->objectType() == BALL) {
		
		Ball* ball;
		Paddle* paddle;

		if (objA->objectType() == BALL)
			ball = static_cast<Ball*>(objectA);
		else if (objB->objectType() == BALL)
			ball = static_cast<Ball*>(objectB);

		if (objA->objectType() == PADDLE)
			paddle = static_cast<Paddle*>(objectA);
		else if (objB->objectType() == PADDLE)
			paddle = static_cast<Paddle*>(objectB);



		
	}
	*/

	//Deleting pointers causes exceptions
	//delete objA;
	objA = NULL;
	//delete objB;
	objB = NULL;
	//delete ball;
	ball = NULL;
	//delete paddle;
	paddle = NULL;
	//delete block;
	block = NULL;
	//delete wall;
	wall = NULL;
	
	
	

	//Paddle* paddle = (Paddle*)(contact->GetFixtureA()->GetBody()->GetUserData());
	//Ball* ball = (Ball*)(contact->GetFixtureB()->GetBody()->GetUserData());
	



	//if (paddle == NULL)
	//{
	//	std::string* name = (std::string*)(contact->GetFixtureA()->GetBody()->GetUserData());
	//	if (*name == "Block") {

	//		contact->GetFixtureA()->GetBody()->SetType(b2_dynamicBody);
	//		contact->GetFixtureA()->GetBody()->SetAwake(true);
	//	}
	//}
	//

	//if (paddle->getName() == "Paddle" && ball->getName() == "Ball")
	//{
	//	//Calculate how much X-direction force to add
	//	//Based on the distance between point of impact and distance to edge of paddle

	//	//Store current velocity
	//	const b2Vec2 currentVelocity = contact->GetFixtureB()->GetBody()->GetLinearVelocity();
	//	//Set velocity to 0, to keep each bounce consistent
	////	contact->GetFixtureB()->GetBody()->SetLinearVelocity(b2Vec2(0, 0));
	//	//Apply Force in opposite direction, with a small boost to Y velocity
	//	contact->GetFixtureB()->GetBody()->ApplyForce(
	//		b2Vec2(currentVelocity.x, -currentVelocity.y * 1.2f + 2),
	//		contact->GetFixtureB()->GetBody()->GetPosition(), true);
	//}

	//Sets colliding only if the ball collides with a block
	//Prevents blocks triggering other blocks

	//if (paddle->name == "Block" && ball->name == "Ball")
	//	colA->colliding = true;
	//else if (colB->name == "Block" && colA->name == "Ball")
	//	colB->colliding = true;

}

//Runs after contact stay (e.g. ball rolls off edge)
void Collision::EndContact(b2Contact* contact) { }

//Page 53 manual for reasons to avoid
//Runs before physics calculations
void Collision::PreSolve(b2Contact* contact, const b2Manifold* oldManifold) { } 

//Runs after physics calculations
void Collision::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) { }