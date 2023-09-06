#include "Input.h"

#include "GLFW/glfw3.h"
#include <iostream>

namespace Engine
{
	static GLFWwindow* _window;

	void Input::SetWindow(GLFWwindow* window)
	{
		_window = window;
	}

	bool Input::GetKey(Keycode key)
	{
		return (glfwGetKey(_window, key) == GLFW_PRESS);
	}

	bool Input::GetKeyUp(Keycode key)
	{
		return (glfwGetKey(_window, key) == GLFW_RELEASE);
	}
	//void Input::GetMouseCallback(/*GLFWcursorposfun mousePos*/)
	//{
	//	//glfwSetCursorPosCallback(_window, mousePos);
	//	//return glm::vec2(0,0);
	//}
	GLFWwindow* Input::GetWindow()
	{
		return _window;
	}
}