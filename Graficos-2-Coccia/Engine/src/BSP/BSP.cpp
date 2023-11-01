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

	void BSP::AddPlane(Plane* plane)
	{
		planes.push_back(plane);

	}

	void BSP::RemoveModel()
	{
		models.clear();
	}

	void BSP::CalculateBSP()
	{
		glm::vec3 pos = Renderer::myRef->GetCamera()->cameraPos;
		for (int i = 0; i < models.size(); i++)
		{
			CalculateBSPMesh(models[i]->structure.meshes[1], pos);
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
			bool cameraIsFront = planes[i]->FrontPlane(cameraPos);

			int verticesInFrontCount = 0;

			for (const glm::vec3& aux : mesh->verticesBoundingBox) {
				if (planes[i]->FrontPlane(mesh->GetPosition() + aux) != cameraIsFront) {
					verticesInFrontCount++;
					if (verticesInFrontCount >= 8) {
						mesh->canDraw = false;
						break;
					}
				}
			}
		}
	}
	float BSP::GetDistanceToPoint(glm::vec3 point)
	{
		// distancia positiva si el punto esta frente al plano
		// distancia negativa si el punto esta espaldas al plano

		glm::vec3 aux;
		aux.x = normal.x * 2;
		aux.y = normal.y * 2;
		aux.z = normal.z * 2;

		return  (glm::dot(point - GetPosition(), normal) + distance) / (aux.x + aux.y + aux.z);

	}

	bool BSPPlane::FrontPlane(glm::vec3 point)
	{
		if (GetDistanceToPoint(point) > 0.0f)
			return true;
		return false;
	}
}