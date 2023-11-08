#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "..\Export\Export.h"
#include "glm\glm\vec3.hpp"
#include "glm\glm\mat4x4.hpp"
#include "../Renderer/Renderer.h"
using namespace glm;
namespace Engine
{
	enum class ENTITY_COLOR
	{
		WHITE, BLACK, GRAY,
		RED, GREEN, BLUE
	};

	struct Transform
	{
		vec3 position;
		vec3 rotation;
		vec3 scale;
		
		vec3 preb_position;
		vec3 preb_rotation;
		vec3 preb_scale;

		vec3 forward;
		vec3 up;
		vec3 right;
	};

	struct GeneralMatrix
	{
		mat4 model;
		mat4 translate;
		mat4 rotateX;
		mat4 rotateY;
		mat4 rotateZ;
		mat4 scale;
		

	};

	class EXPORT_API Entity 
	{
		void SetPrebPosition(vec3 position);
		void SetPrebRotation(vec3 rotation);
		void SetPrebRotationX(float x);
		void SetPrebRotationY(float y);
		void SetPrebRotationZ(float z);
		void SetPrebScale(vec3 scale);

	protected:
		mat4 TRS;
		GeneralMatrix _generalMatrix;

		bool _isTrigger;
		bool _isStatic;
		Renderer* _renderer;

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
		
		vec3 GetPosition();

		bool GetTriggerState();
		bool GetStaticState();

		virtual void TriggerCollision(Entity* other) = 0;
	};
}
#endif