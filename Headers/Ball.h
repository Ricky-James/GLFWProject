#pragma once
#include <GLFW/glfw3.h>
#include <math.h>
#include <Box2D/Box2D.h>
#include "Headers/Object.h"
#include "Headers/Paddle.h"

class Ball : public virtual Object
{

private:

	const float radius = 0.05f;
	b2CircleShape circleShape;
	int lives;

public:

	int objectType() {
		return BALL;
	}

	//Draws ball to screen (+ position)
	void draw() override;
	void setPos(b2Vec2 b2pos);
	void paddleCollision(Paddle *paddle); //For when ball collides with paddle
	bool hasCollided;

	const b2CircleShape getShape();

	void resetPos();


	Ball()
	{
		lives = 3;
		hasCollided = false;
		colour[0] = 255;
		colour[1] = 255;
		colour[2] = 255;

		bodyDef.position.Set(pos.x, pos.y);
		bodyDef.type = b2_dynamicBody;
		bodyDef.linearDamping = 1.0f;
		bodyDef.angularDamping = 0.1f;
		//bodyDef.fixedRotation = true;
		bodyDef.allowSleep = false;
		bodyDef.angularVelocity = 1.0f;

		circleShape.m_p.Set(0, 0); //Position relative to body
		circleShape.m_radius = radius;

		fixtureDef.shape = &circleShape;
		fixtureDef.friction = 0;
		fixtureDef.restitution = 1.0f;

	}
	~Ball() {}
	
};

