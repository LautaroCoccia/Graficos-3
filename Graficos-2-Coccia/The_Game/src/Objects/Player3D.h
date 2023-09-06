#ifndef PLAYER3D_H
#define PLAYER3D_H

#include "..\src\Entity\Entity.h"
#include "..\src\Lights\DirectionalLight.h"
#include "..\src\Lights\PointLight.h"
#include "..\src\Lights/Spotlight.h"
#include "GameBase/GameBase.h"

namespace Engine
{
	class  Player3D : public Entity
	{
		Spotlight* _dLight;
		Cubo* _cubeModel;
		float _movementSpeed;
	public:
		Player3D();
		Player3D(float movementSpeed, const char* texture, const char* texture2, Renderer* renderer);
		~Player3D();
		void SetCubeModel(const char* diffuseMap, const char* specularMap, Renderer* renderer);
		Light* GetLight();
		void Move(float deltaTime);
		void Draw();
		void TriggerCollision(Entity* other) override;

	};

}
#endif // !PLAYER3D