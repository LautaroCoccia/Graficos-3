#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "Light.h"
#include "glm/glm/glm.hpp"
namespace Engine
{
	class EXPORT_API Spotlight : public Light
	{
	private:
		SpotlightData _spotData;

	public:
		Spotlight(Renderer* renderer,glm::vec3 color, glm::vec3 position, glm::vec3 direction);
		~Spotlight();

		void Draw(int i) override;

		glm::vec3 GetPosition();
		glm::vec3 GetDirection();

		void SetPosition(glm::vec3 position);
		void SetDirection(glm::vec3 direction);
		void SetSpotValues(float constant, float linear, float quadratic);
		void SetCutOffs(float cutOff, float outerCutOff);
	};
}
#endif // !SPOTLIGHT_H