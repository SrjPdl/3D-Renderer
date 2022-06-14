#pragma once
#include<glm/glm.hpp>
#include<GLFW/glfw3.h>
class Mouse
{
	private:
		float sensitivity;
		static glm::vec2 change;
		GLFWwindow* window;

		static void handleMouse(GLFWwindow* window, double xPos, double yPos);
		Mouse();
		Mouse(GLFWwindow* window);
	
	public:
		Mouse(const Mouse&) = delete;
		static Mouse& getInstance(GLFWwindow* window);
		glm::vec2 getChange();


};

