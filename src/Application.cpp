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

#include <iostream>

#define SCREENWIDTH 640
#define SCREENHEIGHT 640
#define PTM 5 //Pixels to meter ratio
#define GRAVITY -0.02f

//TO DO:
//PHYSICS
//LOOK INTO REPLACING PADDLE QUADS
//3D?


bool* cursorActive = new bool();
float* cursorXPos = new float();
bool step = false;



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
	b2Vec2 gravity(0.0f, -10.0);
	b2World world(gravity);
	world.SetWarmStarting(true);
	world.SetContinuousPhysics(true);


	//Ground body setup
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(10.0f, 1.0f); //(w,h)
	
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;

	groundBody->CreateFixture(&groundBox, 1.0f);

	//Dynamic body (with mass) setup
	/*b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 15.0f);
	b2Body* body = world.CreateBody(&bodyDef);
*/


	//Shape
	//b2PolygonShape dynamicBox;
	//dynamicBox.SetAsBox(1.2f, 0.2f); //w+h


	//Fixture
	//b2FixtureDef fixtureDef; //new fixture
	//fixtureDef.shape = &dynamicBox; //attach shape & body
	//fixtureDef.density = 1.0f; //A dynamic body should have at least one fixture with non-zero density
	//fixtureDef.friction = 0.3f;
	//


	//body->CreateFixture(&fixtureDef);


	float32 timeStep = 1.0f / 60.0f; //Step integrator (60.0 hz)

	//Box2D suggests velo 8, pos 3. Fewer increases performances but accuracy suffers (box2d doc 2.4)
	//Number of constraint iterations. completely unrelated to step count
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	//**********END B2 INIT*************//BOX 2D INIT
	

	Ball ball;
	Paddle paddle;

	paddle.body = world.CreateBody(&paddle.bodyDef);
	paddle.body->CreateFixture(&paddle.getShape(), 1.0f);

	std::vector<Block> blocks;

	//Instantiate blocks
	float xpos = -0.82f; //Starting co-ords
	float ypos = 0.95f;
	for (int i = 0; i < 7; i++) //Iterating left to right
	{
		for (int n = 0; n < 5; n++) //Top to bottom
		{
			blocks.push_back(Block(xpos, ypos)); //Add to vector at current co-ords
			ypos -= 0.1f; //Reduce Y-coord for each iteration
			//Attach fixture to body and body to world. 1.0f dens.
			blocks.back().body = world.CreateBody(&blocks.back().bodyDef);
			blocks.back().body->CreateFixture(&blocks.back().getShape(), 1.0f);

		}
		ypos = 0.95f; //Reset Y Co-ord for each full iteration of nested loop
		xpos += 0.27f; 
	}
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		/* Setup view: */
		glClear(GL_COLOR_BUFFER_BIT);


		/* Render here */
		
		//Movement

		//Frame advance debugging (R to step)
		if (step)
		{
			world.Step(timeStep, velocityIterations, positionIterations);
			//step = false;
		}
		


		//B2D Sample code
		
		/*
		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();
		blocky.pos.x = position.x / 10;
		blocky.pos.y = position.y / 10;
		blocky.drawBox();
		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
		


		b2Vec2 position2 = body2->GetPosition();
		float32 angle2 = body2->GetAngle();
		blocker.pos.x = position2.x / 10;
		blocker.pos.y = position2.y / 10;
		glColor3f(0, 1, 0.5f);
		blocker.drawBox();*/

		
	
		//Color
		
		
		
		//Drawing

		//Ball
		ball.setColours(1, 0.5f, 0.5f);
		ball.drawBall();

		//Paddle
		glColor3f(paddle.colour[0], paddle.colour[1], paddle.colour[2]);
		b2Vec2 paddlePos = paddle.body->GetPosition();
		paddle.pos.y = box2glfw(paddlePos).y;
		paddle.bodyDef.position = glfw2box(paddle.getPos());
		paddle.drawBox();


		//Block colours
		glColor3f(0, 1, 0.5f);

	

		//Iterator for drawing blocks.
		//Popping blocks will cut them from being drawn.
		for (Block block : blocks)
		{		
			b2Vec2 boxPos = block.body->GetPosition();	
			block.pos = box2glfw(boxPos);
			glColor3f(block.colour[0], block.colour[1], block.colour[2]);
			block.drawBox();
			
		//	printf("%4.2f %4.2f %4.2f\n", pos.x, pos.y, angle);
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
		step = true;
	}
}

static void cursorEnterCallback(GLFWwindow* window, int entered)
{
	if (entered)
	{
		*cursorActive = true;
		std::cout << "Entered" << std::endl;
	}
	else {
		*cursorActive = false;
	}
}

static void cursorPositionCallback(GLFWwindow* window, double x, double y)
{
	//Conversion from pixel co-ord to GL co-ord (-1 to 1)
	//-0.5 to center the cursor/paddle on Y
	//*2 to cover full -1 to 1 range
	(*cursorXPos) = ((x / SCREENWIDTH) - 0.5f) * 2; 

}

void updatePaddlePos(GLFWwindow* window, Paddle& paddle)
{
	if (cursorActive) {
		paddle.setXPos(*cursorXPos);
	}
}

Vector2 box2glfw(b2Vec2 boxPos)
{
	Vector2 newPos;
	std::cout << "box Y: " << boxPos.y << std::endl;
	
	newPos.x = boxPos.x * 5;
	newPos.y = boxPos.y * 5;

	std::cout << "new Y: " << newPos.y << std::endl;
	return newPos;
}

b2Vec2 glfw2box(Vector2 glfwPos)
{
	//DISFUNCTIONAL
	b2Vec2 newPos;

	std::cout << "glfw Y: " << glfwPos.y << std::endl;
	newPos.x = ((glfwPos.x * SCREENWIDTH) - 0.5f) * 2;
	newPos.y = ((glfwPos.y * SCREENWIDTH) - 0.5f) * 2;
	std::cout << "new Y: " << newPos.y << std::endl;
	return newPos;
}