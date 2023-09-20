#include "Game.h"
#include <iostream>
#include <time.h>

namespace Engine
{
	Game::Game(): GameBase()
	{
		_player3D = NULL;
		_camera = NULL;
		_light = NULL;
		//_cube = NULL;

	}

	Game::~Game()
	{
		if (_player3D != NULL)
			delete _player3D;
		if (_camera != NULL)
			delete _camera;
		if (_light != NULL)
			delete _light;
		//if (_cube != NULL)
		//	delete _cube;
	}

	void Game::Start()
	{
		StartEngine(1200, 600, "Coccia Graficos 2");
		srand(time(NULL));

		_camera = new Camera(CameraType::Perspective, 0.1f, 100.0f, 1200, 600, 0.5f);
		_camera->SetCameraMode(CameraMode::FlyCamera);
		
		_model = new Model("res/Models/backpack/backpack.obj");
		//_model = new Model(GetRenderer(),"res/Models/Knuckles/Knuckles.fbx",false,false);
		//_model = new Model(GetRenderer(),"res/Models/Skate/characterMedium.fbx",false,false);
		
		//_model = new Model(GetRenderer(),"res/Models/Cubemap/Cubemap.obj",false,false);
		//_model = new Model(GetRenderer(),"res/Models/Cubemap/Cubemap2.fbx",false,false);
		//_model = new Model(GetRenderer(),"res/Models/Cube/cube.fbx",false,false);
		
		_model->SetPosition(0, 0, 0);

		//_model2 = new Model(GetRenderer(),"res/Models/Skate/characterMedium.fbx", false,false);
		//_model2->SetPosition(0, 1, 0);

		_light = new Spotlight(GetRenderer(),vec3(1,1,1),vec3(1,1,0 ),vec3(1,1,1));
		_light->SetPosition(glm::vec3(0, 1, 0));
		_light->SetLightData(glm::vec3(1, 1, 1), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.5, 0.5, 0.5), vec3(1,0,0));
		_light->SetCutOffs(5, 10);

		_light2 = new DirectionalLight(GetRenderer(), vec3(1, 0, 0), vec3(1, 0, 0));
		//For TPCamera (pos y rot)
		_camera->SetCameraPosition(0, 0, -3);
		_camera->SetCameraRotation(4.37f, 1, 0);
		_camera->SetCameraOffset(7);
		
		//_camera->SetCameraOffset(glm::vec3(0, 0, 0));
		_camera->LookAt(glm::vec3(0, 1, 0));
		
		GetRenderer()->SetCurrentCamera(_camera);

		GetLightManager()->AddNewPoint(GetRenderer(), glm::vec3(1, 1, 1), glm::vec3(5, 1, 5));
		GetLightManager()->AddNewPoint(GetRenderer(), glm::vec3(1, 1, 1), glm::vec3(2, 1, -2));

		GetLightManager()->AddNewSpot(GetRenderer(), glm::vec3(1, 1, 1), _camera->GetPosition(), _camera->_transform.forward);
		GetLightManager()->GetSpot(0)->SetSpotValues(0.01f, 0.3f, 0.1f);
		
		// --------------------------------
		
		_player3D = new Player3D(10, "res/box2.png","res/container2_specular.png", GetRenderer());
		_player3D->SetPosition(0, 0, 0);
		_player3D->GetLight()->SetLightData(glm::vec3(1, 1, 1), glm::vec3(1,1,1), glm::vec3(1, 1, 1), glm::vec3(1,1,1));
		
	}
	
	void Game::Play()
	{
		UpdateEngine(0.5f, 0.5f, 0.5f, 1);
	}

	void Game::Update(float deltaTime)
	{
		if (Input::GetKey(Keycode::ALPHA1))
		{
			glm::vec3 algo =(_model->_transform.scale += deltaTime, _model->_transform.scale += deltaTime, _model->_transform.scale += deltaTime);
			_model->ScaleModel(algo.x, algo.y, algo.z);
		}
		
		_light2->SetDirection(_player3D->_transform.forward);
		_light2->Draw(1);
		_model->Draw();
		
		if (_camera->GetCurrentMode() != CameraMode::FlyCamera)
		{
			_player3D->Move(deltaTime);
		}
		_camera->CameraInput(deltaTime,  _player3D->_transform);

		if (_camera->GetCurrentMode() != CameraMode::FPCamera)
		{
			_player3D->Draw();
		}
		
	}

	void Game::End()
	{
		EndEngine();
	}
}