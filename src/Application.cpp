#include <GLFW/glfw3.h>
#include <iostream> //for debug purposes

#include <Box2D/Box2D.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <thread>
#include "Headers/Ball.h"
#include "Headers/Paddle.h"
#include "Headers/Block.h"

#include <iostream>

#define SCREENWIDTH 640
#define SCREENHEIGHT 640
#define PPM 36 //Pixels per meter ratio for Box2D MKS conversion
#define GRAVITY -0.02f

//TO DO:
//PHYSICS
//LOOK INTO REPLACING PADDLE QUADS
//3D?


bool* cursorActive = new bool();
float* cursorXPos = new float();




//Input callbacks
static void cursorEnterCallback(GLFWwindow* window, int entered);
static void cursorPositionCallback(GLFWwindow* window, double x, double y);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void updatePaddlePos(GLFWwindow* window, Paddle& paddle);

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
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 5.0f);

	groundBody->CreateFixture(&groundBox, 0.0f);

	//Dynamic body (with mass) setup
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 15.0f);
	b2Body* body = world.CreateBody(&bodyDef);

	b2BodyDef bodyDef2;
	bodyDef2.type = b2_dynamicBody;
	bodyDef2.position.Set(0.0f, 30.0f);
	b2Body* body2 = world.CreateBody(&bodyDef2);


	//Shape
	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f); //w+h
	b2PolygonShape dynamicBox2;
	dynamicBox2.SetAsBox(1.0f, 1.0f); //w+h


	//Fixture
	b2FixtureDef fixtureDef; //new fixture
	fixtureDef.shape = &dynamicBox; //attach shape & body
	fixtureDef.density = 1.0f; //A dynamic body should have at least one fixture with non-zero density
	fixtureDef.friction = 0.3f;
	
	b2FixtureDef fixtureDef2; //new fixture
	fixtureDef2.shape = &dynamicBox2; //attach shape & body
	fixtureDef2.density = 1.0f; //A dynamic body should have at least one fixture with non-zero density
	fixtureDef2.friction = 0.3f;

	body->CreateFixture(&fixtureDef);
	body2->CreateFixture(&fixtureDef2);

	float32 timeStep = 1.0f / 60.0f; //Step integrator (60.0 hz)

	//Box2D suggests velo 8, pos 3. Fewer increases performances but accuracy suffers (box2d doc 2.4)
	//Number of constraint iterations. completely unrelated to step count
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	//**********END B2 INIT*************//BOX 2D INIT
	

	Ball ball;
	Paddle paddle;
	std::vector<Block> blocks;
	Block blocky(0,0);
	Block blocker(0, 0);

	//Instantiate blocks
	float xpos = -0.82f; //Starting co-ords
	float ypos = 0.95f;
	for (int i = 0; i < 7; i++) //Iterating left to right
	{
		for (int n = 0; n < 5; n++) //Top to bottom
		{
			blocks.push_back(Block(xpos, ypos)); //Add to vector at current co-ords
			ypos -= 0.1f; //Reduce Y-coord for each iteration
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


		//B2D Sample code
		world.Step(timeStep, velocityIterations, positionIterations);

		b2Vec2 position = body->GetPosition();
		float32 angle = body->GetAngle();
		blocky.pos.x = position.x / 10;
		blocky.pos.y = position.y / 10;
		blocky.drawBox();
		printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
		


		b2Vec2 position2 = body2->GetPosition();
		float32 angle2 = body2->GetAngle();
		blocker.pos.x = 0;
		blocker.pos.y = position2.y / 10;
		glColor3f(0, 1, 0.5f);
		blocker.drawBox();

		
		printf("%4.2f %4.2f %4.2f\n", position2.x, position2.y, angle);

		//Color
		
		
		
		//Drawing

		//Ball
		ball.setColours(1, 0.5f, 0.5f);
		ball.drawBall();

		//Paddle
		glColor3f(paddle.colour[0], paddle.colour[1], paddle.colour[2]);
		paddle.drawBox();


		//Block colours
		glColor3f(0, 1, 0.5f);

	

		//Iterator for drawing blocks.
		//Popping blocks will cut them from being drawn.
		for (Block block : blocks)
		{
		
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