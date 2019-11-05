#pragma once
#include <GLFW/glfw3.h>
#include <math.h>
#include <Box2D/Box2D.h>

class Ball 
{

private:
	
	struct Vector2 {
		float x, y;
	};

	Vector2 pos, spd;
	

	const float radius = 0.05f;
	const float DEG2RAD = 3.14159 / 180;

	float colours[3];


	b2FixtureDef fixtureDef;
	b2CircleShape circleShape;
	

	

public:

	b2BodyDef bodyDef;
	b2Body* body;

	Ball()
	{
		pos.x = 0; pos.y = 0;
		spd.x = 0; spd.y = 0;
		colours[0] = 255;
		colours[1] = 255;
		colours[2] = 255;

		bodyDef.position.Set(pos.x, pos.y);
		bodyDef.type = b2_dynamicBody;
		bodyDef.linearDamping = 1.0f;
		bodyDef.angularDamping = 1.0f;

		circleShape.m_p.Set(0, 0); //Position relative to body
		circleShape.m_radius = radius;

		fixtureDef.shape = &circleShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.restitution = 10.0f;

		
	}

	float getxspeed() const { return spd.x; }
	float getyspeed() const { return spd.y; }
	float getxpos()   const { return pos.x; }
	float getypos()   const { return pos.y; }

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

	
};

