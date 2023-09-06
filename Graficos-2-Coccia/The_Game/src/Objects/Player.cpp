#include "Player.h"
#include <iostream>
namespace Engine
{
	Player::Player(Renderer* renderer, const glm::ivec2& tileDimensions, float speed, Camera* camera) : Sprite(renderer, tileDimensions)
	{
		_speed = speed;
		//_camera = camera;
		//_x = 0;
		//_z = 0;


		_transform.position = glm::vec3(0.0f, 0.0f, 0.0f);

		_transform.rotation = glm::vec3(0.0f, 1.0f, 0.0f);;

		_transform.up = glm::vec3(0.0f, 1.0f, 0.0f);
		_transform.right = glm::normalize(glm::cross(_transform.up, _transform.rotation));

		_transform.up = glm::cross(_transform.rotation, _transform.right);

		_transform.forward = glm::vec3(0.0f, 0.0f, -1.0f);

	}
	
	Player::~Player()
	{

	}

	void Player::Move(float deltaTime)
	{
		/*if (Input::GetKey(Keycode::W))
		{
			GetAnimation()->UpdateFrame(deltaTime);
			SetRotationY(180);

			SetPosition(_transform.position.x, _transform.position.y , _transform.position.z + (_speed * deltaTime));
		}
		else if (Input::GetKey(Keycode::S))
		{
			GetAnimation()->UpdateFrame(deltaTime);
			DrawAnimation(GetAnimation()->GetUVsFromVector(GetAnimation()->GetCurrentFrame()));
			SetRotationY(0);

			SetPosition(_transform.position.x, _transform.position.y , _transform.position.z - (_speed * deltaTime));
		}
		else if (Input::GetKey(Keycode::A))
		{
			GetAnimation()->UpdateFrame(deltaTime);
			DrawAnimation(GetAnimation()->GetUVsFromVector(GetAnimation()->GetCurrentFrame()));
			SetRotationY(180);
		
			SetPosition(_transform.position.x - (_speed * deltaTime), _transform.position.y, _transform.position.z);
		}
		else if (Input::GetKey(Keycode::D))
		{
			GetAnimation()->UpdateFrame(deltaTime);
			DrawAnimation(GetAnimation()->GetUVsFromVector(GetAnimation()->GetCurrentFrame()));
			SetRotationY(0);
		
			SetPosition(_transform.position.x + (_speed * deltaTime), _transform.position.y, _transform.position.z);
		}
		else 
		{
			//GetAnimation()->UpdateFrame(deltaTime);
			DrawAnimation(GetAnimation()->GetUVs(36));
		}*/
		_transform.forward = glm::normalize(_transform.rotation);
		_transform.right = glm::normalize(glm::cross(glm::vec3(0, 1, 0), _transform.forward));
		_transform.up = glm::normalize(glm::cross(_transform.forward, _transform.right));

		if (Input::GetKey(Keycode::W))
			_transform.position += _speed * _transform.forward * deltaTime;
		if (Input::GetKey(Keycode::S))
			_transform.position -= _speed * _transform.forward * deltaTime;
		if (Input::GetKey(Keycode::A))
			_transform.position -= glm::normalize(glm::cross(_transform.forward, _transform.up)) * _speed * deltaTime;
		if (Input::GetKey(Keycode::D))
			_transform.position += glm::normalize(glm::cross(_transform.forward, _transform.up)) * _speed * deltaTime;
		
		std::cout << _transform.position.x << _transform.position.y << _transform.position.z << std::endl;

		//_camera->SetCameraPosition(_transform.position);

		/*if (Input::GetKey(Keycode::W))
		{
			_z += (_speed * deltaTime);
		}
		else if (Input::GetKey(Keycode::S))
		{
			_z -= (_speed * deltaTime);

		}
		else if (Input::GetKey(Keycode::A))
		{
			_x -= (_speed * deltaTime);

		}
		else if (Input::GetKey(Keycode::D))
		{
			_x += (_speed * deltaTime);

		}
		_transform.position = _transform.right * _x + _transform.forward * _z;
		_transform.rotation = _camera->GetRotation();*/
	}

	void Player::TriggerCollision(Entity* other)
	{
		if (!other->GetStaticState())
		{
			glm::vec3 newPos = _transform.position;
			ReturnToPrevPosition();
			newPos -= _transform.position;

			other->SetPosition(other->_transform.position + newPos);
		}
		else
		{
			ReturnToPrevPosition();
		}
	}
}