#pragma once

#include<GL/glew.h>
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include "Mouse.h"
#include "Keyboard.h"
class Camera
{

	private:
		GLFWwindow* window;
		glm::vec3 position;
		glm::vec3 u;
		glm::vec3 v;
		glm::vec3 n;
		uint32_t uView;
		uint32_t uProjection;
		uint32_t uPosition;
		uint32_t program;
		float yaw;
		float pitch;
		float moveSpeed;
		
		
		Mouse& mouse;
		Keyboard& keyboard;

		void mouseInput();
		void keyboardInput(float deltaTime);
	public:
		Camera(GLFWwindow* window, uint32_t shaderProgram);

		void update(float deltaTime, glm::mat4* projectionMatrix);
		glm::mat4 getViewMat();
		glm::vec3 getViewDir();
		
};

