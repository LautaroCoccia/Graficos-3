#include "Entity.h"
#include "glm/gtc/matrix_transform.hpp"

namespace Engine
{
	Entity::Entity(/*Renderer* renderer*/)
	{
		//_renderer = renderer;

		SetPosition(0, 0, 0);
		SetRotation(0, 0, 0);
		SetScale(1, 1, 1);

		SetPrebPosition(_transform.position);
		SetPrebRotation(_transform.rotation);
		SetPrebScale(_transform.scale);

		_isTrigger = false;
		_isStatic = false;
		_transform.forward = glm::vec3(0, 0, 1);
		_transform.up = glm::vec3(0, 1, 0);
		_transform.right = glm::vec3(0, 1, 0);
	}

	Entity::~Entity()
	{

	}

	void Entity::SetPosition(float x, float y, float z)
	{
		SetPrebPosition(_transform.position);

		_transform.position.x = x;
		_transform.position.y = y;
		_transform.position.z = z;

		_generalMatrix.translate = glm::translate(glm::mat4(1.0f), _transform.position);
		UpdateMatrix();
	}

	void Entity::SetPosition(glm::vec3 position)
	{
		SetPrebPosition(_transform.position);

		_transform.position = position;

		_generalMatrix.translate = glm::translate(glm::mat4(1.0f), _transform.position);
		UpdateMatrix();
	}

	void Entity::SetRotation(float x, float y, float z)
	{
		SetPrebRotation(_transform.rotation);

		_transform.rotation = { x, y, z };
		_generalMatrix.rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
		_generalMatrix.rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
		_generalMatrix.rotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
		UpdateMatrix();
	}

	void Entity::SetRotation(glm::vec3 rotation)
	{
		SetPrebRotation(_transform.rotation);

		_transform.rotation = rotation;
		_generalMatrix.rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		_generalMatrix.rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		_generalMatrix.rotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		UpdateMatrix();
	}

	void Entity::SetRotationX(float x)
	{
		SetPrebRotationX(0);

		_transform.rotation.x = x;
		_generalMatrix.rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
		UpdateMatrix();
	}

	void Entity::SetRotationY(float y)
	{
		SetPrebRotationY(0);

		_transform.rotation.y = y;
		_generalMatrix.rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
		UpdateMatrix();
	}

	void Entity::SetRotationZ(float z)
	{
		SetPrebRotationZ(0);

		_transform.rotation.z = z;
		_generalMatrix.rotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
		UpdateMatrix();
	}

	void Entity::SetScale(float x, float y, float z)
	{
		SetPrebScale(_transform.scale);

		_transform.scale.x = x;
		_transform.scale.y = y;
		_transform.scale.z = z;

		_generalMatrix.scale = glm::scale(glm::mat4(1.0f), _transform.scale);
		UpdateMatrix();
	}

	void Entity::SetScale(glm::vec3 scale)
	{
		SetPrebScale(_transform.scale);

		_transform.scale = scale;

		_generalMatrix.scale = glm::scale(glm::mat4(1.0f), _transform.scale);
		UpdateMatrix();
	}

	// --------------------------------
	// Se utiliza para poder updatear la matris "model" que controla todas posiciones y datos de la figura

	void Entity::UpdateMatrix()
	{
		_generalMatrix.model =
			_generalMatrix.translate *
			_generalMatrix.rotateX *
			_generalMatrix.rotateY *
			_generalMatrix.rotateZ *
			_generalMatrix.scale;
	}

	void Entity::ReturnToPrevTransform()
	{
		SetPosition(_transform.preb_position);
		SetRotation(_transform.preb_rotation);
		SetScale(_transform.preb_scale);
	}

	void Entity::ReturnToPrevPosition()
	{
		SetPosition(_transform.preb_position);
	}

	void Entity::ReturnToPrevRotation()
	{
		SetRotation(_transform.preb_rotation);
	}

	void Entity::ReturnToPrevScale()
	{
		SetScale(_transform.preb_scale);
	}

	// --------------------------------
	// Se utiliza para las colisiones

	void Entity::SetTriggerState(bool state)
	{
		_isTrigger = state;
	}

	void Entity::SetStaticState(bool state)
	{
		_isStatic = state;
	}
	glm::vec3 Entity::GetPosition()
	{
		return _transform.position;
	}
	bool Entity::GetTriggerState()
	{
		return _isTrigger;
	}

	bool Entity::GetStaticState()
	{
		return _isStatic;
	}

	// --------------------------------
	// Funciones usadas para setear las posiciones anteriores antes de hacer un SetPos, etc
	void Entity::SetPrebPosition(glm::vec3 position)
	{
		_transform.preb_position = position;
	}

	void Entity::SetPrebRotation(glm::vec3 rotation)
	{
		_transform.preb_rotation = rotation;
	}

	void Entity::SetPrebRotationX(float x)
	{
		_transform.preb_rotation.x = x;
	}

	void Entity::SetPrebRotationY(float y)
	{
		_transform.preb_rotation.y = y;
	}

	void Entity::SetPrebRotationZ(float z)
	{
		_transform.preb_rotation.z = z;
	}

	void Entity::SetPrebScale(glm::vec3 scale)
	{
		_transform.preb_scale = scale;
	}
}