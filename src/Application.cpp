#include <GLFW/glfw3.h>

//#include <Box2D/Box2D.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Headers/Ball.h"
#include "Headers/Paddle.h"


//TO DO:
//LEARN HOW TO INCORPORATE INPUT
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
		paddle.drawPaddle();
		
		


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

