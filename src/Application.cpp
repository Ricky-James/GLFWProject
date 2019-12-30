#include <GLFW/glfw3.h>
#include <iostream> //for debug purposes
#include <Box2D/Box2D.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include "Headers/Vector2.h"
#include "Headers/Ball.h"
#include "Headers/Paddle.h"
#include "Headers/Block.h"
#include "Headers/Collision.h"
#include <iostream>

#define SCREENWIDTH 640
#define SCREENHEIGHT 640

//Used in input callbacks
bool* g_cursorActive = new bool();
double* g_cursorXPos = new double();

//Input callbacks
static void cursorEnterCallback(GLFWwindow* window, int entered);
static void cursorPositionCallback(GLFWwindow* window, double x, double y);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void updatePaddlePos(GLFWwindow* window, Paddle& paddle);

//Simple conversion functions
Vector2 box2glfw(b2Vec2 boxPos);
b2Vec2 glfw2box(Vector2 glfwPos);

int main(void)
{
	
	GLFWwindow* window;

	if (!glfwInit())
		exit(EXIT_FAILURE);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	

	// Create a windowed mode window and its OpenGL context
	window = glfwCreateWindow(SCREENWIDTH, SCREENHEIGHT, "Box2D Project", NULL, NULL);
	
	

	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1); //Refresh rate, 0 causes tearing/vsync issues

	

	//Input callback setup
	glfwSetKeyCallback(window, key_callback); 
	glfwSetCursorEnterCallback(window, cursorEnterCallback);
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //hides cursor and prevents movement from being disabled when outside window
	
	//View frustum
	
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	

	//**********START B2 INIT*************
	
	b2Vec2 gravity(0.0f, -9.8f);
	b2World* world = new b2World(gravity);
	world->SetWarmStarting(true);
	world->SetContinuousPhysics(true);

	//b2Contact Listener for collision detection
	Collision *collider = new Collision();
	world->SetContactListener(collider);


	const float32 timeStep = 1.0f / 60.0f; //Step integrator (60.0 hz)

	//Box2D suggests velo 8 or 6, pos 3 or 2. Fewer increases performances but accuracy suffers (box2d doc 2.4)
	//Number of constraint iterations. completely unrelated to step count
	int32 velocityIterations = 8;
	int32 positionIterations = 3;
	//**********END B2 INIT*************//BOX 2D INIT
	
	//Game object initialising in the box2d World
	Ball* ball = new Ball();
	ball->body = world->CreateBody(&ball->bodyDef);
	ball->body->CreateFixture(&ball->getShape(), 1.0f);
	ball->body->SetGravityScale(0.2f);
	ball->body->SetUserData(ball);


	Paddle* paddle = new Paddle();
	paddle->body = world->CreateBody(&paddle->bodyDef);
	paddle->body->CreateFixture(&paddle->getShape(), 1.0f);
	paddle->body->SetGravityScale(1.0f);
	paddle->body->SetUserData(paddle);

	std::vector<Block*> blocks;
	{
		float xpos = -0.82f; //Starting co-ords
		float ypos = 0.90f;
		for (int i = 0; i < 7; i++) //Iterating left to right
		{
			for (int n = 0; n < 5; n++) //Top to bottom
			{
				blocks.push_back(new Block(xpos, ypos, 0.24f, 0.04f, b2_staticBody)); //Add to vector at current co-ords
				ypos -= 0.1f; //Reduce Y-coord for each iteration
			}
			ypos = 0.90f; //Reset Y Co-ord for each full iteration of nested loop
			xpos += 0.27f;
		}
	}
	for (std::vector<Block*>::iterator itr = blocks.begin(); itr != blocks.end(); itr++)
	{
		int index = std::distance(blocks.begin(), itr);

		//Attach fixture to body and body to world. 1.0f dens.
		blocks.at(index)->body = world->CreateBody(&blocks.at(index)->bodyDef);
		blocks.at(index)->body->CreateFixture(&blocks.at(index)->getShape(), 0.1f);
		blocks.at(index)->body->SetGravityScale(0.2f);
		
		blocks.at(index)->body->SetUserData(blocks.at(index));
	}



	//Assigning position and sizes of walls for boundaries
	//left/right/top/bottom.
	//May decide to purge the bottom and/or top barrier later
	std::vector<Block*> walls;
	walls.push_back(new Block(-1, 0, 0.05f, 2.0f  , b2_kinematicBody));
	walls.push_back(new Block(1 , 0, 0.05f, 2.0f  , b2_kinematicBody));
	walls.push_back(new Block(0 , 1, 2.0f , 0.05f , b2_kinematicBody));
	//walls.push_back(Block(0 , -1, 2.0f , 0.05f, b2_kinematicBody));

	for (std::vector<Block*>::iterator itr = walls.begin(); itr != walls.end(); itr++)
	{
		int index = std::distance(walls.begin(), itr);

		walls.at(index)->body = world->CreateBody(&walls.at(index)->bodyDef);
		walls.at(index)->body->CreateFixture(&walls.at(index)->getShape(), 1.0f);
		walls.at(index)->setColours(235, 85, 52);
		walls.at(index)->typeNumber = 4;
		walls.at(index)->body->SetUserData(walls.at(index));
	}

	double previousTime = glfwGetTime();
	double lag = 0.0f;

	///MAIN GAME LOOP///

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		///Using https://gameprogrammingpatterns.com/game-loop.html
		//Time system keeps framerate and updates consistent between machines
		//Best to iterate calculations BEFORE making any other physics changes
		double currentTime = glfwGetTime();
		double elapsedTime = currentTime - previousTime;
		previousTime = currentTime;
		lag += elapsedTime;
		while (lag >= timeStep)
		{
			world->Step(timeStep, velocityIterations, positionIterations);
			lag -= timeStep;
		}
		//Step forward once per loop iteration
		

	
		if (ball->hasCollided)
			ball->paddleCollision(paddle);
		

		/* Setup view: */
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.1f, 0.1f, 1.0f); //Background colour


		/* Resolve any collisions */

		/* Render here */

		//Ball
		ball->setPos(ball->body->GetPosition());
		ball->draw();

		//Paddle drawing
		//Paddle rotation changes in accordance with X position
		//paddle->updateRotation();
		//Position updated in mouse callback
		paddle->draw();

	

		for (Block* wall : walls)
		{
			wall->draw(); //unnecessary to draw, drawing for debug purposes
		}

		//Popping blocks will cut them from being drawn.
		for (int i = 0; i < blocks.size(); i++)
		{		
			if (blocks[i]->isCollided() == true)
			{
				blocks[i]->body->SetType(b2_dynamicBody);
			}


			blocks[i]->draw();

			//Check if box pos.y is < -1.1, pop from vec and delete if so.
			if (blocks[i]->body->GetPosition().y < -1.1f)
			{
				//Erase blocks if they fall far off screen
				delete blocks[i];
				blocks.erase(blocks.begin() + i);
				if (blocks.empty())
				{
					//Win condition
				}
			}
		}




		//Reset ball if it falls too far
		if (ball->body->GetPosition().y < -2.0f)
			ball->resetPos();
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		updatePaddlePos(window, *paddle);
		glfwPollEvents();


	}

	//Pointer cleanup
	delete world; 
	world = NULL;
	delete[] g_cursorActive;
	g_cursorActive = NULL;
	delete[] g_cursorXPos;
	g_cursorXPos = NULL;
	delete ball;
	ball = NULL;
	delete paddle;
	paddle = NULL;

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE) {
		delete[] g_cursorActive;
		g_cursorActive = NULL;
		delete[] g_cursorXPos;
		g_cursorXPos = NULL;

		glfwDestroyWindow(window);
		glfwTerminate();
		exit(EXIT_SUCCESS);
	}
}


static void cursorEnterCallback(GLFWwindow* window, int entered)
{
	if (entered)
	{
		*g_cursorActive = true;
	}
	else {
		*g_cursorActive = false;
	}
}

static void cursorPositionCallback(GLFWwindow* window, double x, double y)
{
	//Conversion from pixel co-ord to GLFW co-ord (-1 to 1)
	//-0.5 to center the cursor/paddle on Y
	//*2 to cover full -1 to 1 range
	(*g_cursorXPos) = ((x / SCREENWIDTH) - 0.5f) * 2; 

}

void updatePaddlePos(GLFWwindow* window, Paddle& paddle)
{
	//Update xpos of both glfw and b2body
	if (g_cursorActive) {
		paddle.updatePosition((float)*g_cursorXPos);
	}
}

Vector2 box2glfw(b2Vec2 boxPos) //Vector conversion
{
	Vector2 newPos;

	newPos.x = boxPos.x;
	newPos.y = boxPos.y;

	return newPos;
}

b2Vec2 glfw2box(Vector2 glfwPos) //Vector conversion
{
	//DISFUNCTIONAL
	b2Vec2 newPos;
	newPos.x = glfwPos.x;
	newPos.y = glfwPos.y;
	return newPos;
}