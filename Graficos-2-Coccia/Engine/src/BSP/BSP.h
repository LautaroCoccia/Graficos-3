#ifndef BSP_H
#define BSP_H
#include "../Export/Export.h"
#include "../3D/Model.h"
#include "glm/vec3.hpp"
#include <iostream>
#include <vector>
using namespace glm;
using namespace std;

namespace Engine
{
	class EXPORT_API BSP
	{
	private:
		struct Plane
		{
			vec3 _normal;
			vec3 _distance;
		};
		std::vector<Model*> models;
		std::vector<Plane*> planes;

	public:
		BSP(string name, const char* path, vec3 inNormal);
		~BSP();
		void AddModel(Model* newModel);
		void AddPlane(Plane* plane);
		void RemoveModel();
		void CalculateBSP();
		void CalculateBSPMesh(Mesh* mesh, vec3 cameraPos);
		float GetDistanceToPoint(glm::vec3 point);
		bool FrontPlane(glm::vec3 point);
	};
}
#endif


