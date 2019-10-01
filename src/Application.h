void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods, Ball ball)
{
	if (key == GLFW_KEY_E && action == GLFW_REPEAT) {
		ball.moveRight(true);
	}

}
