#ifndef WINDOW_H
#define WINDOW_H

#include "..\Export\Export.h"

struct GLFWmonitor;
struct GLFWwindow;

namespace Engine
{
	class EXPORT_API Window
	{
		GLFWwindow* _window;

	public:
		Window();
		~Window();
	
		int CreateWindow(int width, int height, const char* title, GLFWmonitor* monitor);
		void InitWindow();
		void DestroyWindow();
		int WindowShouldClose();
		void SwapBuffers();
		void ClearWindow(float r, float g, float b, float a);
		GLFWwindow* ReturnWindow();
	};
}

#endif