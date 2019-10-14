#include <GLFW/glfw3.h>
#include <iostream> //for debug purposes

#include <Box2D/Box2D.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include "Headers/Ball.h"
#include "Headers/Paddle.h"
#include "Headers/Block.h"

#include <iostream>

#define SCREENWIDTH 640
#define SCREENHEIGHT 640
#define PPM 36 //Pixels per meter ratio for Box2D MKS conversion

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
	

	//Create Box2D World

	b2Vec2 gravity(0.0f, -10.0f);
	b2World* world = new b2World(gravity);
	world->SetWarmStarting(true);
	world->SetContinuousPhysics(true);

	b2BodyDef* bodyDef = new b2BodyDef();
	b2Body* groundBody = world->CreateBody(bodyDef);


	Ball ball;
	Paddle paddle;
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
		
		

		//updateInput(window, paddle);
		
		//Color
		
		
		
		//Drawing

		//Ball
		ball.setColours(0, 1, 0.5f);
		ball.drawBall();

		//Paddle
		glColor4f(paddle.colour[0], paddle.colour[1], paddle.colour[2], 0.5f);
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