#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "..\Export\Export.h"
#include "glm\glm\vec3.hpp"
#include "glm\glm\mat4x4.hpp"

using namespace glm;
namespace Engine
{
	struct Transforms
	{
		vec3 position;
		vec3 rotation;
		vec3 scale;

		vec3 localPosition;
		vec3 localRotation;
		vec3 localScale;

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
		unsigned int modelUniform;
	};
	class EXPORT_API Transform
	{
	private:
		
	protected:

		void SetPrebPosition(vec3 position);
		void SetPrebRotation(vec3 rotation);
		void SetPrebRotationX(float x);
		void SetPrebRotationY(float y);
		void SetPrebRotationZ(float z);
		void SetPrebScale(vec3 scale);
	public:
		GeneralMatrix _generalMatrix;
		Transforms _transform;
		
		Transform();
		~Transform();


		void SetPosition(float x, float y, float z);
		void SetPosition(glm::vec3 position);

		void UpdateMatrix();
		void ReturnToPrevTransform();
		void ReturnToPrevPosition();
		void ReturnToPrevRotation();
		void ReturnToPrevScale();
		
		void SetRotation(float x, float y, float z);
		void SetRotation(glm::vec3 rotation);
		void SetRotationX(float x);
		void SetRotationY(float y);
		void SetRotationZ(float z);

		void SetScale(float x, float y, float z);
		void SetScale(glm::vec3 scale);

		vec3 GetPosition();
	};
}
#endif // !TRANSFORM
