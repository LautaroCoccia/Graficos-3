#ifndef BSP_H
#define BSP_H
#include "../Export/Export.h"
#include "../3D/Model.h"
#include "LogicalPlane.h"
#include <iostream>
#include <vector>
using namespace glm;
using namespace std;

namespace Engine
{
	class EXPORT_API BSP
	{
	private:
		std::vector<Model*> models;
		std::vector<LogicalPlane*> planes;

	public:
		BSP();
		~BSP();
		void AddModel(Model* newModel);
		void AddPlane(LogicalPlane* plane);
		void RemoveModel();
		void CalculateBSP();
		void CalculateBSPMesh(Mesh* mesh, vec3 cameraPos);
	};
}
#endif


