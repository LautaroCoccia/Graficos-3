#ifndef D_Light
#define D_Light

#include "Light.h"
namespace Engine
{
	class EXPORT_API  DirectionalLight : public Light
	{
		DirectionLightData _directionData;

	public:
		DirectionalLight(Renderer* renderer, glm::vec3 color, glm::vec3 direction);
		~DirectionalLight();

		void Draw(int i) override;
		void SetDirection(glm::vec3 direction);

	};
}
#endif // !D_Light

