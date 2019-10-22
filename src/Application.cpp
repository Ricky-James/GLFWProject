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


	////Ground body setup
	//b2BodyDef groundBodyDef;
	//groundBodyDef.type = b2_staticBody;
	//groundBodyDef.position.Set(0.0f, -10.0f);
	//b2Body* groundBody = world.CreateBody(&groundBodyDef);

	//b2PolygonShape groundBox;
	//groundBox.SetAsBox(10.0f, 1.0f); //(w,h)
	//
	//b2FixtureDef fixtureDef;
	//fixtureDef.shape = &groundBox;
	//fixtureDef.density = 1.0f;
	//fixtureDef.friction = 0.3f;

	//groundBody->CreateFixture(&groundBox, 1.0f);


	float32 timeStep = 1.0f / 60.0f; //Step integrator (60.0 hz)

	//Box2D suggests velo 8 or 6, pos 3 or 2. Fewer increases performances but accuracy suffers (box2d doc 2.4)
	//Number of constraint iterations. completely unrelated to step count
	int32 velocityIterations = 6;
	int32 positionIterations = 2;
	//**********END B2 INIT*************//BOX 2D INIT
	

	Ball ball;
	Paddle paddle;

	paddle.body = world.CreateBody(&paddle.bodyDef);
	paddle.body->CreateFixture(&paddle.getShape(), 1.0f);
	paddle.body->SetGravityScale(0.0f);
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
			
			//step = false;
		}
		world.Step(timeStep, velocityIterations, positionIterations);

		
		//Drawing

		//Ball
		ball.setColours(1, 0.5f, 0.5f);
		ball.drawBall();

		//Paddle
		glColor3f(paddle.colour[0], paddle.colour[1], paddle.colour[2]);
		paddle.pos.y = box2glfw(paddle.body->GetPosition()).y;
		paddle.bodyDef.position = glfw2box(paddle.getPos());
		paddle.drawBox(paddle.body->GetPosition());


		//Block colours
		glColor3f(0, 1, 0.5f);


		//Debug messages:
	//	std::cout << "Paddle X: " << paddle.bodyDef.position.x << std::endl;
		std::cout << "Block 0Y " << blocks.at(0).body->GetPosition().y << std::endl;
	

		//Iterator for drawing blocks.
		//Popping blocks will cut them from being drawn.
		for (Block block : blocks)
		{		
			block.pos = box2glfw(block.body->GetPosition());
			block.body->SetGravityScale(0.1f);
			glColor3f(block.colour[0], block.colour[1], block.colour[2]);
			block.drawBox(block.body->GetPosition());
			
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
	//Update xpos of both glfw and b2body
	if (cursorActive) {
		paddle.setXPos(*cursorXPos);
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