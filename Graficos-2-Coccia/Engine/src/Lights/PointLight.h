#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

namespace Engine
{
	class EXPORT_API PointLight : public Light
	{
	private:
		PointLightData _pointData;

	public:
		PointLight(Renderer* renderer, glm::vec3 color, glm::vec3 position);
		~PointLight();

		void Draw(int isActive) override;

		glm::vec3 GetPosition();

		void SetPosition(glm::vec3 position);
		void SetColor(glm::vec3 color);
		void SetPointValues(float constant, float linear, float quadratic);
	};
};

#endif

