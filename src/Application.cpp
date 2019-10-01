#include <GLFW/glfw3.h>

//#include <Box2D/Box2D.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "Ball.h"

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

	/*const float DEG2RAD = 3.14159 / 180;
	const float radius = 0.05f;*/
	
	Ball ball;

	

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Setup view: */
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / static_cast<float>(height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		/* Render here */
		//Movement
		
		//Color
		
		
		
		
		
	
		
		//Drawing
		glBegin(GL_POLYGON);
		ball.drawBall();
		glColor3f(100, 100, 100);
		glEnd();
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}