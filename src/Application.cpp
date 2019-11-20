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
#define DEG2RAD 0.0174533

//TODO
//Refactor Ball to inherit from Object
//Collision

//Used in input callbacks
bool* g_cursorActive = new bool();
float* g_cursorXPos = new float();

//Just for debugging really
bool step = false;
Ball ball;

void createBlocks(std::vector<Block> &blocks, b2World &world);


//Input callbacks
static void cursorEnterCallback(GLFWwindow* window, int entered);
static void cursorPositionCallback(GLFWwindow* window, double x, double y);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void updatePaddlePos(GLFWwindow* window, Paddle& paddle);

Vector2 box2glfw(b2Vec2 boxPos);
b2Vec2 glfw2box(Vector2 glfwPos);

int main(void)
{

	GLFWwindow* window;
	
	/* Initialize the library */
	if (!glfwInit())
		exit(EXIT_FAILURE);

	

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCREENWIDTH, SCREENHEIGHT, "OpenGL Project", NULL, NULL);
	int* count;
	

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

	


	float32 timeStep = 1.0f / 60.0f; //Step integrator (60.0 hz)

	//Box2D suggests velo 8 or 6, pos 3 or 2. Fewer increases performances but accuracy suffers (box2d doc 2.4)
	//Number of constraint iterations. completely unrelated to step count
	int32 velocityIterations = 8;
	int32 positionIterations = 3;
	//**********END B2 INIT*************//BOX 2D INIT
	

	
	ball.body = world->CreateBody(&ball.bodyDef);
	ball.body->CreateFixture(&ball.getShape(), 1.0f);
	ball.body->SetGravityScale(1.0f);


	Paddle paddle;

	//Assigning position and sizes of walls for boundaries
	//left/right/top/bottom.
	//May decide to purge the bottom and/or top barrier later
	std::vector<Block> walls;
	walls.push_back(Block(-1, 0, 0.05f, 2.0f  , b2_kinematicBody));
	walls.push_back(Block(1 , 0, 0.05f, 2.0f  , b2_kinematicBody));
	walls.push_back(Block(0 , 1, 2.0f , 0.05f , b2_kinematicBody));
	walls.push_back(Block(0 , -1, 2.0f , 0.05f, b2_kinematicBody));

	for (std::vector<Block>::iterator itr = walls.begin(); itr != walls.end(); itr++)
	{
		int index = std::distance(walls.begin(), itr);
		Block *currentWall = &walls.at(index);
		currentWall->setName("Wall", std::distance(walls.begin(), itr + 1));
		currentWall->body = world->CreateBody(&currentWall->bodyDef);
		currentWall->body->CreateFixture(&currentWall->getShape(), 1.0f);
		currentWall->body->SetGravityScale(1.0f);
		currentWall->setColours(235, 85, 52);
	}



	paddle.body = world->CreateBody(&paddle.bodyDef);
	paddle.body->CreateFixture(&paddle.getShape(), 1.0f);
	paddle.body->SetGravityScale(1.0f);
	std::vector<Block> blocks;

	//Instantiate blocks
	createBlocks(blocks, *world);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		/* Setup view: */
		glClear(GL_COLOR_BUFFER_BIT);


		/* Render here */
		
		//Movement

		//Step toggled by pressing R
		if (step)
		{
			world->Step(timeStep, velocityIterations, positionIterations);
		}
		

		//Drawing

		//Ball
		ball.setPos(ball.body->GetPosition());


		ball.drawBall();

		
		
		//Paddle
		
		paddle.body->SetTransform(paddle.body->GetPosition(), paddle.body->GetAngle()); 
		paddle.drawBox();

		std::cout << "Body -> GetAngle(): " << paddle.body->GetAngle() << std::endl;
	

		for (Block wall : walls)
		{
			wall.drawBox(); //unnecessary to draw, drawing for debug purposes
		}

		//Iterator for drawing blocks.
		//Popping blocks will cut them from being drawn.
		for (Block block : blocks)
		{		
			block.pos = box2glfw(block.body->GetPosition());
			
			
			block.drawBox();
			

		}
		if (blocks.empty())
		{
			//Win condition!
		}
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */

		updatePaddlePos(window, paddle);
		glfwPollEvents();

	}

	delete[] world;
	world = NULL;
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE) {
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(EXIT_SUCCESS);
	}

	if (key == GLFW_KEY_R && action == GLFW_PRESS) //Frame advance tool
	{
		step = !step;
	}

	if (key == GLFW_KEY_T && action == GLFW_PRESS)
	{
		ball.ballToPaddle(b2Vec2(1.0f, 3.0f));
	}	
	if (key == GLFW_KEY_E && action == GLFW_PRESS)
	{
		ball.ballToPaddle(b2Vec2(-1.0f, 3.0f));
	}

}

void createBlocks(std::vector<Block> &blocks, b2World &world)
{
	float xpos = -0.82f; //Starting co-ords
	float ypos = 0.90f;
	int count = 0;
	for (int i = 0; i < 7; i++) //Iterating left to right
	{
		for (int n = 0; n < 5; n++) //Top to bottom
		{
			blocks.push_back(Block(xpos, ypos, 0.24f, 0.04f, b2_staticBody)); //Add to vector at current co-ords
			ypos -= 0.1f; //Reduce Y-coord for each iteration
			//Attach fixture to body and body to world. 1.0f dens.
			blocks.back().body = world.CreateBody(&blocks.back().bodyDef);
			blocks.back().body->CreateFixture(&blocks.back().getShape(), 1.0f);
			blocks.back().body->SetGravityScale(1.0f);
			blocks.back().setName("Block", count);
			std::cout << blocks.back().getName() << std::endl;
			count++;
		}
		ypos = 0.90f; //Reset Y Co-ord for each full iteration of nested loop
		xpos += 0.27f;
	}
}


static void cursorEnterCallback(GLFWwindow* window, int entered)
{
	if (entered)
	{
		*g_cursorActive = true;
		std::cout << "Entered" << std::endl;
	}
	else {
		*g_cursorActive = false;
	}
}

static void cursorPositionCallback(GLFWwindow* window, double x, double y)
{
	//Conversion from pixel co-ord to GL co-ord (-1 to 1)
	//-0.5 to center the cursor/paddle on Y
	//*2 to cover full -1 to 1 range
	(*g_cursorXPos) = ((x / SCREENWIDTH) - 0.5f) * 2; 

}

void updatePaddlePos(GLFWwindow* window, Paddle& paddle)
{
	//Update xpos of both glfw and b2body
	if (g_cursorActive) {
		paddle.setXPos(*g_cursorXPos);
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