#include "BSP.h"

namespace Engine
{

	BSP::BSP()
	{
	}

	BSP::~BSP()
	{
	}

	void BSP::AddModel(Model* newModel)
	{
		models.push_back(newModel);
	}

	void BSP::AddPlane(LogicalPlane* plane)
	{
		planes.push_back(plane);

	}

	void BSP::RemoveModel()
	{
		models.clear();
	}

	void BSP::CalculateBSP()
	{
		glm::vec3 pos = Renderer::_staticRenderer->GetCurrentCamera()->GetPosition();
		//scout << "BSP cam pos: " << pos.x << " , " << pos.y << " , "<< pos.z << endl;
		for (int i = 0; i < models.size(); i++)
		{
			CalculateBSPMesh(models[i]->_model.meshes[1], pos);
		}
	}

	void BSP::CalculateBSPMesh(Mesh* mesh, glm::vec3 cameraPos)
	{

		for (int i = 0; i < mesh->children.size(); i++)
		{
			CalculateBSPMesh(mesh->children[i], cameraPos);
		}

		mesh->canDraw = true;
		for (int i = 0; i < planes.size(); i++)
		{

			bool cameraIsFront = planes[i]->GetSide(cameraPos);
			if (cameraIsFront)
				cout << "mismo lado que plano " << i << endl;
			else 
				cout << "Nop" << i << endl;
			int verticesInFrontCount = 0;
			if(planes[i]->GetSide(mesh->GetPosition()) != cameraIsFront)
				cout << "Nop estan del mismo lado" << i << endl;

			for (const glm::vec3& aux : mesh->verticesBoundingBox) {
				if (planes[i]->GetSide(mesh->GetPosition() + aux) != cameraIsFront) {
					verticesInFrontCount++;
					if (verticesInFrontCount >= 8) {
						mesh->canDraw = false;
						break;
					}
				}
			}
		}
	}
}