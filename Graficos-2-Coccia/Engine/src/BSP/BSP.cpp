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
		for (int i = 0; i < models.size(); i++)
		{
			CalculateBSPMesh(models[i]->_model.meshes[i], pos);
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
			bool onSideCamera = planes[i]->GetSide(cameraPos);
			int verticesInFrontCount = 0;

			for (const glm::vec3& aux : mesh->verticesBoundingBox) {
				if (planes[i]->GetSide(mesh->GetPosition() + aux) != onSideCamera) {
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