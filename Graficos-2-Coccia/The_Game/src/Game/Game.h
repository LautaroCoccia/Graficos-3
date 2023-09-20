#ifndef GAME_H
#define GAME_H

#include "GameBase/GameBase.h"
#include "../Objects/Player.h"
#include "../Objects/Player3D.h"
#include "../../Engine/src/3D/Model.h"
namespace Engine
{
	class Game : public GameBase
	{
	private:
		Camera* _camera;
		Player3D* _player3D;
		Spotlight* _light;
		DirectionalLight* _light2;
		Model* _model;
		Model* _model2;
		//Cube* _cube;

	public:
		Game();
		~Game();

		void Start();
		void Play();
		void Update(float deltaTime) override;
		void End();
	};
}

#endif;