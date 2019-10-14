#include <GLFW/glfw3.h>
#include <iostream> //for debug purposes

//#include <Box2D/Box2D.h>
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

//TO DO:
//INPUT
//PHYSICS
//LOOK INTO REPLACING PADDLE QUADS
//3D?

float* cursorXPos = new float();

static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos);

void updateInput(GLFWwindow* window, Paddle &paddle)
{
	paddle.setXPos(*cursorXPos);
	
	std::cout << "Xpos: " << (*cursorXPos) << std::endl;
}

bool cursorActive;

void cursorEnterCallback(GLFWwindow* window, int entered);
static void cursorPositionCallback(GLFWwindow* window, double x, double y);

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

	
	glfwSetCursorPosCallback(window, cursorPositionCallback); //Cursor input
	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	glfwSetKeyCallback(window, key_callback); //Unused
	
	glfwSetKeyCallback(window, key_callback);

	glfwSetCursorEnterCallback(window, cursorEnterCallback);
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //hides cursor
	
	//View frustum
	float ratio;
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	ratio = width / static_cast<float>(height);
	glViewport(0, 0, width, height);
	


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

		glLoadIdentity();
		ball.drawBall();
		glLoadIdentity();
		paddle.drawBox();
		
		

		//Iterator for drawing blocks.
		//Popping blocks will cut them from being drawn.
		for (Block block : blocks)
		{
			glLoadIdentity();
			block.drawBox();
		}
		if (blocks.empty())
		{
			//Win condition!
		}
	


		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();



	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE) {
		glfwDestroyWindow(window);
		glfwTerminate();
		exit(EXIT_SUCCESS);
	}
}

void cursorEnterCallback(GLFWwindow* window, int entered)
{
	if (entered)
	{
		cursorActive = true;
		std::cout << "Entered" << std::endl;
	}
	else {
		cursorActive = false;
	}
}

static void cursorPositionCallback(GLFWwindow* window, double x, double y)
{
	if (cursorActive)
	{
		float test = x * 0.5 + 0.5 + 0.5 / SCREEN_WIDTH;
		std::cout << test << std::endl;
	//	std::cout << x << ", " << y << std::endl;
	}

static void cursorPositionCallback(GLFWwindow* window, double xPos, double yPos)
{
	//Conversion from pixel co-ord to GL co-ord (-1 to 1)
	//-0.5 to center the cursor/paddle on Y
	//*2 to cover full -1 to 1 range
	(*cursorXPos) = ((xPos / SCREENWIDTH) - 0.5f) * 2; 

}