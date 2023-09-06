#include "Game.h"
#include <iostream>
#include <time.h>

namespace Engine
{
	Game::Game(): GameBase()
	{
		_quad = NULL;
		_player3D = NULL;
		_roboBob = NULL;
		_wall1 = NULL;
		_wall2 = NULL;
		_box = NULL;
		_camera = NULL;
		_light = NULL;
		//_cube = NULL;

		_cubito = NULL;
	}

	Game::~Game()
	{
		if (_player3D != NULL)
			delete _player3D;
		if (_roboBob != NULL)
			delete _roboBob;
		if (_wall1 != NULL)
			delete _wall1;
		if (_wall2 != NULL)
			delete _wall2;
		if (_box != NULL)
			delete _box;
		if (_camera != NULL)
			delete _camera;
		if (_light != NULL)
			delete _light;
		if (_cubito != NULL)
			delete _cubito;
		//if (_cube != NULL)
		//	delete _cube;
	}

	void Game::Start()
	{
		StartEngine(1200, 600, "Coccia Graficos 2");
		srand(time(NULL));

		_camera = new Camera(CameraType::Perspective, 0.1f, 100.0f, 1200, 600, 0.5f);
		_camera->SetCameraMode(CameraMode::FlyCamera);

		_model = new Model(GetRenderer(),"res/Models/backpack/backpack.obj",false,false);
		_model->SetPosition(0, 0, 0);
		//_model->SetScale(0.25, 0.25, 0.25);

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
		//_quad = new Shape(GetRenderer());
		//_quad->InitShape(TypeOfShape::Quad);
		//_quad->SetColor(ENTITY_COLOR::WHITE);
		//_quad->SetPosition(0, 1, 0);
		// --------------------------------
		
		_wall1 = new Sprite(GetRenderer(), "res/RockWall.jpg");

		//_wall1->InitTexture();
		//_wall1->ImportTexture("res/RockWall.jpg");
		_wall1->SetPosition(0, -1, 0);
		_wall1->SetRotation(90, 0, 0);
		_wall1->SetScale(10,10,10);
		_wall1->SetStaticState(true);
		//GetCollisionManager()->AddNewObject(_wall1);
		
		// --------------------------------
		//_wall2 = new Sprite(GetRenderer());
		//_wall2->InitTexture();
		//_wall2->ImportTexture("res/RockWall.jpg");
		//_wall2->SetRotation(0, 0, 0);
		//_wall2->SetPosition(0, 0, 0);
		//_wall2->SetStaticState(true);
		//GetCollisionManager()->AddNewObject(_wall2);
		
		// --------------------------------
		
		_player3D = new Player3D(10, "res/wall.png","res/container2_specular.png", GetRenderer());
		_player3D->SetPosition(0, 0, 0);
		_player3D->GetLight()->SetLightData(glm::vec3(1, 1, 1), glm::vec3(1,1,1), glm::vec3(1, 1, 1), glm::vec3(1,1,1));
		// --------------------------------

		//_box = new Sprite(GetRenderer());
		//_box->InitTexture();
		//_box->ImportTexture("res/wall.png");
		//_box->SetPosition(0, 0, 0);

		//GetCollisionManager()->AddNewObject(_box);
		
		// --------------------------------

		//_roboBob = new Player(GetRenderer(), ivec2(9,5), 10,_camera);
		//_roboBob->GetAnimation()->AddFrame(0.5, 0, 7);
		//
		//_roboBob->InitTexture();
		//_roboBob->ImportTexture("res/character_robot_sheet.png");
		//_roboBob->SetPosition(0, 0, 0);
		//GetCollisionManager()->AddNewObject(_roboBob);

		//_camera->SetEntity(_roboBob);

		// --------------------------------

		//_cube = new Cube("res/crate1_diffuse.png", GetRenderer());
		//_cube->SetPosition(0, 0, 0);

		//_cubito = new Cubo("res/box2.png", "res/container2_specular.png" ,GetRenderer());
		_cubito = new Cubo("res/box2.png", "res/container2_specular.png",GetRenderer());
		//_cubito = new Cubo("res/matrix.jpg", "res/matrix.jpg","res/matrix.jpg" ,GetRenderer());
		_cubito->SetMaterial(glm::vec3(1, 1, 1), glm::vec3(1,1,1), glm::vec3(1,1,1), 32);
		//_cubito->SetScale(1, 1, 1);
		_cubito->SetPosition(0, 0, 0);
		_cubito->SetScale(10, 10, 10);
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
		//_model->ScaleModel(0,0,0);
		//_camera->SetCameraPosition(_roboBob->_transform.position);
		//_roboBob->Move(deltaTime);
		//_camera->CameraInput(deltaTime,  _roboBob->_transform);
		
		//_wall2->Draw();
		
		//_cube->Draw();

		//_quad->Draw();
		_light2->SetDirection(_player3D->_transform.forward);
		//_light2->SetLightData(vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1), vec3(1, 1, 1));
		//_light->Draw(1);
		_light2->Draw(1);
		//_model->Draw();
		//_model->SetPosition(_player3D->GetPosition());
		_model->Draw();
		//_model2->Draw();
		_cubito->Draw();
		if (_camera->GetCurrentMode() != CameraMode::FlyCamera)
		{
			_player3D->Move(deltaTime);
		}
		_camera->CameraInput(deltaTime,  _player3D->_transform);

		if (_camera->GetCurrentMode() != CameraMode::FPCamera)
		{
			_player3D->Draw();
		}
		_wall1->Draw();
		
		//_box->Draw();
		
		//GetCollisionManager()->CheckAllCollisions();
		//GetLightManager()->GetSpot(0)->SetDirection(_camera->_transform.forward);
		//GetLightManager()->GetSpot(0)->SetPosition(_camera->GetPosition());
		//
		//GetLightManager()->DrawLights();
	}

	void Game::End()
	{
		EndEngine();
	}
}