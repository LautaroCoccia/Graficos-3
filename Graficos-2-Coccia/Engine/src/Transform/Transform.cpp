#include "Transform.h"
#include "glm/gtc/matrix_transform.hpp"
#include <iostream>
using namespace std;

namespace Engine
{
	Transform::Transform()
	{
		
	}
	Transform::~Transform()
	{

	}
	void Transform::SetPosition(float x, float y, float z)
	{
		SetPrebPosition(_transform.position);

		_transform.position.x = x;
		_transform.position.y = y;
		_transform.position.z = z;

		_generalMatrix.translate = glm::translate(glm::mat4(1.0f), _transform.position);
		UpdateMatrix();
		//std::cout << "position: " << _transform.position.x << " " << _transform.position.y << " " << _transform.position.z << endl;
	}

	void Transform::SetPosition(glm::vec3 position)
	{
		SetPrebPosition(_transform.position);

		_transform.position = position;

		_generalMatrix.translate = glm::translate(glm::mat4(1.0f), _transform.position);
		UpdateMatrix();
	}

	void Transform::SetRotation(float x, float y, float z)
	{
		SetPrebRotation(_transform.rotation);

		_transform.rotation = { x, y, z };
		_generalMatrix.rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
		_generalMatrix.rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
		_generalMatrix.rotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
		UpdateMatrix();
	}

	void Transform::SetRotation(glm::vec3 rotation)
	{
		SetPrebRotation(_transform.rotation);

		_transform.rotation = rotation;
		_generalMatrix.rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
		_generalMatrix.rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
		_generalMatrix.rotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
		UpdateMatrix();
	}

	void Transform::SetRotationX(float x)
	{
		SetPrebRotationX(0);

		_transform.rotation.x = x;
		_generalMatrix.rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
		UpdateMatrix();
	}

	void Transform::SetRotationY(float y)
	{
		SetPrebRotationY(0);

		_transform.rotation.y = y;
		_generalMatrix.rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
		UpdateMatrix();
	}

	void Transform::SetRotationZ(float z)
	{
		SetPrebRotationZ(0);

		_transform.rotation.z = z;
		_generalMatrix.rotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
		UpdateMatrix();
	}

	void Transform::SetScale(float x, float y, float z)
	{
		SetPrebScale(_transform.scale);

		_transform.scale.x = x;
		_transform.scale.y = y;
		_transform.scale.z = z;

		_generalMatrix.scale = glm::scale(glm::mat4(1.0f), _transform.scale);
		UpdateMatrix();
	}

	void Transform::SetScale(glm::vec3 scale)
	{
		SetPrebScale(_transform.scale);

		_transform.scale = scale;

		_generalMatrix.scale = glm::scale(glm::mat4(1.0f), _transform.scale);
		UpdateMatrix();
	}

	// --------------------------------
	// Se utiliza para poder updatear la matris "model" que controla todas posiciones y datos de la figura

	void Transform::UpdateMatrix()
	{
		_generalMatrix.model =_generalMatrix.translate *_generalMatrix.rotateX * _generalMatrix.rotateY *
			_generalMatrix.rotateZ * _generalMatrix.scale;
	}

	void Transform::ReturnToPrevTransform()
	{
		SetPosition(_transform.preb_position);
		SetRotation(_transform.preb_rotation);
		SetScale(_transform.preb_scale);
	}

	void Transform::ReturnToPrevPosition()
	{
		SetPosition(_transform.preb_position);
	}

	void Transform::ReturnToPrevRotation()
	{
		SetRotation(_transform.preb_rotation);
	}

	void Transform::ReturnToPrevScale()
	{
		SetScale(_transform.preb_scale);
	}
	// --------------------------------
	// Funciones usadas para setear las posiciones anteriores antes de hacer un SetPos, etc
	void Transform::SetPrebPosition(glm::vec3 position)
	{
		_transform.preb_position = position;
	}

	void Transform::SetPrebRotation(glm::vec3 rotation)
	{
		_transform.preb_rotation = rotation;
	}

	void Transform::SetPrebRotationX(float x)
	{
		_transform.preb_rotation.x = x;
	}

	void Transform::SetPrebRotationY(float y)
	{
		_transform.preb_rotation.y = y;
	}

	void Transform::SetPrebRotationZ(float z)
	{
		_transform.preb_rotation.z = z;
	}

	void Transform::SetPrebScale(glm::vec3 scale)
	{
		_transform.preb_scale = scale;
	}
	vec3 Transform::GetPosition()
	{
		return _transform.position;
	}
}