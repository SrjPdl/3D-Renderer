#include "Keyboard.h"

uint32_t Keyboard::key = NULL;

Keyboard::Keyboard(GLFWwindow* window)
    :window(window)
{
}

Keyboard& Keyboard::getInstance(GLFWwindow* window)
{
    static Keyboard instance(window);
    return instance;
}

bool Keyboard::isKeyDown(uint32_t key)
{
    bool action=glfwGetKey(window, key);
    return (action== (GLFW_PRESS || GLFW_REPEAT));
}
