#ifndef GAME_BASE_H
#define GAME_BASE_H

#include "../Window/Window.h"
#include "../Renderer/Renderer.h"
#include "../Shape/Shape.h"
#include "../Camera/Camera.h"
#include "../Sprite/Sprite.h"
#include "../Cube/Cube.h"
#include "../Cube/Cubo.h"
#include "../Lights/Light.h"
#include "../Animation/Animation.h"
#include "../Input/Input.h"
#include "../Time/Time.h"
#include "../CollisionManager/CollisionManager.h"
#include "../Lights/LightsManager.h"
#include "glm/glm/glm.hpp"
namespace Engine
{
	class EXPORT_API GameBase
	{
		Renderer* _renderer;
		Window* _window;
		CollisionManager* _collisionManager;
		Camera* _camera;
	public:
		LightManager* _lightManager;
		GameBase();
		~GameBase();

		int StartEngine(int width, int height, const char* windowName);
		void UpdateEngine(float r, float g, float b, float a);
		void EndEngine();

		virtual void Update(float deltatime) = 0;

		void SetCamera(CameraType type, float near, float far,float height, float width,float sensibility);
		void SetCameraPosition(float x, float y, float z);

		Renderer* GetRenderer();
		CollisionManager* GetCollisionManager();
		LightManager* GetLightManager();
	};
}

#endif;