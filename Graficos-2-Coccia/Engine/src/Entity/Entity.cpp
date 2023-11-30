#include "Entity.h"
#include "glm/gtc/matrix_transform.hpp"


namespace Engine
{
	Entity::Entity(/*Renderer* renderer*/) : Transform()
	{
		_renderer = _renderer->_staticRenderer;

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

		_generalMatrix.model = mat4(1.0);
		_generalMatrix.translate = mat4(1.0);
		_generalMatrix.rotateX = mat4(1.0);
		_generalMatrix.rotateY = mat4(1.0);
		_generalMatrix.rotateZ = mat4(1.0);
		_generalMatrix.scale = mat4(1.0);
	}

	Entity::~Entity() 
	{

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

	bool Entity::GetTriggerState()
	{
		return _isTrigger;
	}

	bool Entity::GetStaticState()
	{
		return _isStatic;
	}

	GeneralMatrix Entity::GetGeneralMatrix()
	{
		return _generalMatrix;
	}

	Transforms Entity::GetTransform()
	{
		return _transform;
	}
}