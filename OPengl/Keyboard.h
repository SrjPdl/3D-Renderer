#pragma once
#include<GLFW/glfw3.h>

class Keyboard
{
	private:
		static uint32_t key;
		GLFWwindow* window;
		Keyboard(GLFWwindow* window);
	public:
		Keyboard(const Keyboard&) = delete;
		static Keyboard& getInstance(GLFWwindow* window);
		bool isKeyDown(uint32_t key);
};

