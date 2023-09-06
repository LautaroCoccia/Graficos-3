#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "..\Export\Export.h"
#include "glm\glm\vec3.hpp"
#include "glm\glm\mat4x4.hpp"

namespace Engine
{
	enum class ENTITY_COLOR
	{
		WHITE, BLACK, GRAY,
		RED, GREEN, BLUE
	};

	struct Transform
	{
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
		
		glm::vec3 preb_position;
		glm::vec3 preb_rotation;
		glm::vec3 preb_scale;

		glm::vec3 forward;
		glm::vec3 up;
		glm::vec3 right;
	};

	struct GeneralMatrix
	{
		glm::mat4 model;
		glm::mat4 translate;
		glm::mat4 rotateX;
		glm::mat4 rotateY;
		glm::mat4 rotateZ;
		glm::mat4 scale;
		

	};

	class EXPORT_API Entity 
	{
		void SetPrebPosition(glm::vec3 position);
		void SetPrebRotation(glm::vec3 rotation);
		void SetPrebRotationX(float x);
		void SetPrebRotationY(float y);
		void SetPrebRotationZ(float z);
		void SetPrebScale(glm::vec3 scale);

	protected:
		//Renderer* _renderer;
		glm::mat4 TRS;
		GeneralMatrix _generalMatrix;

		bool _isTrigger;
		bool _isStatic;

	public:
		Entity();
		~Entity();

		Transform _transform;

		void SetPosition(float x, float y, float z);
		void SetPosition(glm::vec3 position);

		void SetRotation(float x, float y, float z);
		void SetRotation(glm::vec3 rotation);
		void SetRotationX(float x);
		void SetRotationY(float y);
		void SetRotationZ(float z);

		void SetScale(float x, float y, float z);
		void SetScale(glm::vec3 scale);

		void UpdateMatrix();
		void ReturnToPrevTransform();
		void ReturnToPrevPosition();
		void ReturnToPrevRotation();
		void ReturnToPrevScale();

		void SetTriggerState(bool state);
		void SetStaticState(bool state);
		
		glm::vec3 GetPosition();

		bool GetTriggerState();
		bool GetStaticState();

		virtual void TriggerCollision(Entity* other) = 0;
	};
}
#endif