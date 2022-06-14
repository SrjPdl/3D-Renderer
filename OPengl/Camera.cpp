#include "Camera.h"

glm::mat4 Camera::getViewMat()
{
	return glm::lookAt(position, position + n, v);
}

glm::vec3 Camera::getViewDir()
{
	return -n;
}

Camera::Camera(GLFWwindow* window, uint32_t shaderProgram)
	:window(window),
	position(glm::vec3(10.f, 10.f, 20.f)),
	u(glm::vec3(1.f, 0.f, 0.f)),
	v(glm::vec3(0.f, 1.f, 0.f)),
	n(glm::vec3(1.f, 1.f, -1.f)),
	program(shaderProgram),
	yaw(-90.f),
	pitch(0),
	moveSpeed(7.f),
	mouse(Mouse::getInstance(window)),
	keyboard(Keyboard::getInstance(window))
{
	//getting uniform location
	uProjection = glGetUniformLocation(program, "projection");
	uView = glGetUniformLocation(program, "view");
	uPosition = glGetUniformLocation(program, "cameraPosition");
}

void Camera::mouseInput()
{
	glm::vec2 cameraRotation = mouse.getChange();

	yaw += cameraRotation.x;
	pitch += cameraRotation.y;

	//clamping value of pitch between -90 and 90
	if (pitch <= -90.f)
	{
		pitch = -89.9f;
	}
	else if(pitch >= 90.f)
	{
		pitch = 89.9f;
	}

	n.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	n.y = sin(glm::radians(pitch));
	n.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	u = glm::cross(glm::vec3(n), glm::vec3(0.f, 1.f, 0.f));

	v = glm::cross(glm::vec3(u), glm::vec3(n));
}

void Camera::keyboardInput(float deltaTime)
{
	if (keyboard.isKeyDown(GLFW_KEY_W))
	{
		position += n * moveSpeed * deltaTime;
	}
	else if (keyboard.isKeyDown(GLFW_KEY_S))
	{
		position -= n * moveSpeed * deltaTime;
	}
	else if (keyboard.isKeyDown(GLFW_KEY_A))
	{
		position -= u * moveSpeed * deltaTime;
	}
	else if (keyboard.isKeyDown(GLFW_KEY_D))
	{
		position += u * moveSpeed * deltaTime;
	}
}

void Camera::update(float deltaTime, glm::mat4* projectionMatrix)
{
	
	mouseInput();
	keyboardInput(deltaTime);

	glUniformMatrix4fv(uProjection, 1, GL_FALSE, glm::value_ptr(*projectionMatrix));
	glUniformMatrix4fv(uView, 1, GL_FALSE, glm::value_ptr(getViewMat()));
	glUniform3fv(uPosition, 1, glm::value_ptr(this->position));
}
