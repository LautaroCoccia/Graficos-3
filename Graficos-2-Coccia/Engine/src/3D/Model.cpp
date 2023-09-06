#include "Model.h"

namespace Engine
{

	Model::Model(Renderer* rend, string const& path, bool flipUVs, bool gamma) : gammaCorrection(gamma)
	{
		_model.renderer = rend;

		ModelImporter::loadModel(path, flipUVs, _model);
	}

	void Model::MoveModel(glm::vec3 direction) 
	{
		for (int i = 0; i < _model.meshes.size(); i++)
		{
			_model.meshes[i].SetPosition(direction.x, direction.y, direction.z);
		}
	}

	void Model::ScaleModel(float x, float y, float z) 
	{
		for (int i = 0; i < _model.meshes.size(); i++)
		{
			if (x < 0 || y < 0 || z < 0) 
			{
				x = 0; y = 0; z = 0;
			}
			_model.meshes[i].SetScale(x, y, z);
		}
	}

	void Model::Draw()
	{
		_model.renderer->UpdateProgram(TRS);
		for (unsigned int i = 0; i < _model.meshes.size(); i++)
		{
			_model.meshes[i].Draw();
		}
	}
	void Model::TriggerCollision(Entity* other) { }

}
