#ifndef LIGHT_H
#define LIGHT_H

#include "../Export/Export.h"
#include "../Renderer/Renderer.h"

namespace Engine
{
	enum LightType
	{
		Directional,
		Point,
		SpotLight
	};
	class EXPORT_API Light
	{
	protected:

		LightData _lightData;
		Renderer* _renderer;
	public:
		Light(Renderer* renderer, glm::vec3 color);
		~Light();
		void SetLightData(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 lightColor);
		void SetPosition(glm::vec3 position);
		virtual void Draw(int isActive) = 0;
	};
}
#endif