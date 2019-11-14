#pragma once
#include <GLFW/glfw3.h>
#include <math.h>
#include <Box2D/Box2D.h>
#include <string>
#include "Headers/Object.h"

class Ball : public Object
{

private:

	const float radius = 0.05f;
	const float DEG2RAD = 3.14159 / 180;

	b2CircleShape circleShape;
	
	
	

public:

	b2BodyDef bodyDef;
	b2Body* body;
	bool contacting;

	Ball()
	{
		setName("Ball");

		pos.x = 0; 
		pos.y = 0;
		angle = 0;
		colour[0] = 255;
		colour[1] = 255;
		colour[2] = 255;

		bodyDef.position.Set(pos.x, pos.y);
		bodyDef.type = b2_dynamicBody;
		bodyDef.linearDamping = 1.0f;
		bodyDef.angularDamping = 1.0f;

		bodyDef.allowSleep = false;

		circleShape.m_p.Set(0, 0); //Position relative to body
		circleShape.m_radius = radius;

		fixtureDef.shape = &circleShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.restitution = 10.0f;

		//body->SetUserData((void*)data);
	}

	

	//Draws ball to screen (+ position)
	void drawBall() const;
	void setPos(b2Vec2 b2pos);
	void setColours(float r, float g, float b);

	const b2CircleShape getShape() {
		return circleShape;
	}

	void ballToPaddle(b2Vec2 force)
	{
		body->ApplyForce(force, body->GetPosition(), true);
	}

	void startContact() { contacting = true; }

	void endContact() { contacting = false; }

	
};

