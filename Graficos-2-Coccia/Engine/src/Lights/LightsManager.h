#ifndef L_MANAGER_H
#define L_MANAGER_H

#include <vector>

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

using namespace std;

namespace Engine
{
	const int MAX_INDIVIDUALS_LIGHTS = 4;

	class EXPORT_API LightManager
	{
	private:
		DirectionalLight* _directional;
		vector<PointLight*> _pointsList;
		vector<Spotlight*> _spotsList;

	public:
		LightManager();
		~LightManager();

		void AddNewDirectional(Renderer* renderer, glm::vec3 color, glm::vec3 direction);
		void AddNewPoint(Renderer* renderer,glm::vec3 color, glm::vec3 position);
		void AddNewSpot(Renderer* renderer, glm::vec3 color, glm::vec3 position, glm::vec3 direction);

		void RemoveDirectional();
		void RemovePoint(int i);
		void RemoveSpot(int i);

		DirectionalLight* GetDirectional();
		PointLight* GetPoint(int i);
		Spotlight* GetSpot(int i);

		void DrawLights();
	};
};
#endif // !L_MANAGER_H