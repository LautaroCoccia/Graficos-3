#include "FPCamera.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm\gtc\type_ptr.hpp"
#include "../Input/Input.h"
namespace Engine
{
	FPCamera::FPCamera()
	{
		//_entity = NULL;
	}
	FPCamera::FPCamera(CameraType type, float near, float far, float height, float width, float sensibility):Camera( type, near, far, height, width, sensibility)
	{
		//_entity = NULL;
	}
	FPCamera::~FPCamera()
	{

	}
	//void FPCamera::SetEntity(Entity* entity)
	//{
	//	_entity = entity;
	//}
	void FPCamera::CameraInput(float deltaTime)
	{
		glfwSetCursorPosCallback(Input::GetWindow(), MouseCallback);
		glfwSetInputMode(Input::GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		
		//_direction.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		//_direction.y = sin(glm::radians(_pitch));
		//_direction.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
		//_cameraFront = glm::normalize(_direction);
		//_cameraRight = glm::normalize(glm::cross(glm::vec3(0, 1, 0), _cameraFront));
		//_cameraUp = glm::normalize(glm::cross(_cameraFront, _cameraRight));
		//
		//if (_entity != NULL)
		//{
		//	_entity->SetRotation(_direction.x, 0, _direction.z);
		//}
	}
}