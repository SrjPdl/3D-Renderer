#include "Mouse.h"

glm::vec2 Mouse::change = glm::vec2(0, 0);

void Mouse::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	static glm::vec2 lastPos;
	static bool isInitialState=true;

	if (isInitialState)
	{
		lastPos = glm::vec2(xPos, yPos);
		isInitialState = false;
	}
	change.x = xPos - lastPos.x;
	change.y = lastPos.y - yPos;
	lastPos = glm::vec2(xPos, yPos);
}

Mouse::Mouse(GLFWwindow* window)
	:sensitivity(0.1f),
	 window(window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, handleMouse);
}

Mouse& Mouse::getInstance(GLFWwindow *window)
{
	static Mouse instance(window);
	return instance;
}

glm::vec2 Mouse::getChange()
{
	glm::vec2 temp = change*sensitivity;
	change = glm::vec2(0, 0);
	return temp;
}

