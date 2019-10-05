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
	std::vector<Block*> blocks;

	//Instantiate blocks
	float xpos;
	float ypos;
	for (int i = 0, xpos = -0.85f; i < 5; i++, xpos += 0.3)
	{
		for (int n = 0, ypos = 0.95f; n < 5; n++, ypos -= 0.1f)
		{
			blocks.push_back(new Block(xpos, ypos));
		}
	}
	/*int c;
	c = static_cast<int>(blocks.size());
	
	exit(c);*/
	
	
	

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

		for (std::vector<Block*>::iterator currentBlock = blocks.begin(); currentBlock != blocks.end(); ++currentBlock)
		{
			//currentBlock.drawBox();
			Block* blockCheck = dynamic_cast<Block*>(*currentBlock);
			
			if (blockCheck != NULL)
			{
				(*blockCheck).drawBox();
			}
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

