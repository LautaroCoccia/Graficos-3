#ifndef FPCAMERA
#include "../Camera/Camera.h"
//#include "../Entity/Entity.h"
namespace Engine
{
	class EXPORT_API FPCamera : virtual  Camera
	{
		//Entity* _entity;
		float _yaw = -90.f;
		float _pitch = 0.0f;
		float _lastX = 800.f / 2;
		float _lastY = 600.f / 2;

		bool _firstMouse = true;

		float _sensitivity = 0.5f;
	public:
		FPCamera();
		FPCamera(CameraType type, float near, float far, float height, float width, float sensibility);
		~FPCamera();
		//void SetEntity(Entity* entity);
		void CameraInput(float deltaTime);
	};
}
#define FPCAMERA
#endif // !FPCAMERA

