#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include "..\Export\Export.h"
#include "..\Entity\Entity.h"
#include "glm\glm\mat4x4.hpp"
#include "..\Shader\Shader.h"
#include "..\Window\Window.h"

namespace Engine
{
	enum class CameraType {
		Perspective,
		Ortho
	};
	enum class CameraMode {
		FlyCamera,
		FPCamera,
		TPCamera,
		StaticCamera
	};
	class EXPORT_API Camera : public Entity
	{
	private:
		
		const float cameraSpeed = 10.0f; // adjust accordingly

		glm::mat4 _projection;
		glm::mat4 _view;

		//glm::vec3 _camPos;
		float _camOffset;
		CameraMode _currentMode;

		glm::vec3 asd;

		//glm::vec3 _cameraTarget;
		//glm::vec3 _cameraPos;
		//glm::vec3 _cameraFront;
		//glm::vec3 _cameraUp;
		//glm::vec3 _cameraDirection;
		//glm::vec3 _cameraRotation;
		//glm::vec3 _cameraRight;
		//glm::vec3 _up;

	public:
		Camera();
		Camera(CameraType type, float near, float far, float height, float width, float sensibility);
		~Camera();

		//void UpdateCameraVectors();
		void UpdateView();
		//void UpdateMVP(glm::mat4 model);
		//void SetIndex(unsigned int shaderId);
		void SetCameraValues(CameraType type, float near, float far, float height, float width, float sensibility);
		//void SetCameraTarget(Transform& cameraTarget);
		void LookAt(glm::vec3 target);
		void SetCameraOffset(float _camOffset);
		void SetCameraPosition(float x, float y, float z);
		void SetCameraPosition(glm::vec3 position);
		void SetCameraRotation(float x, float y, float z);
		void SetCameraRotation(glm::vec3 vec);
		void SetCameraDirection(float x, float y, float z);
		void SetCameraMode(CameraMode mode);
		void DefaultSettings();
		void CameraInput(float deltaTime, Transform& transformObj);
		static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
		glm::mat4 GetView();
		glm::mat4 GetProjection();
		glm::vec3 GetRotation();
		CameraMode GetCurrentMode();

		void TriggerCollision(Entity* other);
	};
}
#endif