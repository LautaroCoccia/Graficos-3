#ifndef PLAYER_H
#define PLAYER_H

#include "GameBase/GameBase.h"
#include "../src/Camera/Camera.h"
namespace Engine
{
	class Player : public Sprite
	{
		float _speed;
		//Camera* _camera;

	public:
		Player(Renderer* renderer, const glm::ivec2& tileDimensions, float speed, Camera* camera);
		~Player();

		void Move(float deltaTime);
		void TriggerCollision(Entity* other) override;
	};
}
#endif