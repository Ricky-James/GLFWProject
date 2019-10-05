#include <GLFW/glfw3.h>

//#include <Box2D/Box2D.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include "Headers/Ball.h"
#include "Headers/Paddle.h"
#include "Headers/Block.h"


//TO DO:
//INPUT
//PHYSICS
//BUILD UPPER BLOCKS INTO VECTOR
//LOOK INTO REPLACING PADDLE QUADS
//3D?

void updateInput(GLFWwindow* window, Paddle &paddle)
{
	if (GLFW_KEY_E == GLFW_PRESS) {
		paddle++;
		printf("E press");
	}
}


int main(void)
{
	
	GLFWwindow* window;
	/* Initialize the library */
	if (!glfwInit())
		exit(EXIT_FAILURE);

	
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 640, "OpenGL Project", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	glfwSwapInterval(1); //Refresh rate, 0 causes tearing/vsync issues

	void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);
	glfwSetKeyCallback(window, key_callback);
	
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

		ball.drawBall();
		paddle.drawBox();
		
		

		//Iterator for drawing blocks.
		//Popping blocks will cut them from being drawn.
		for (Block &block : blocks)
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
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);

}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_SPACE) {
		printf("Test");
	}
}

