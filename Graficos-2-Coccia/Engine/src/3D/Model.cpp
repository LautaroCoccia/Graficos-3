#include "Model.h"

namespace Engine
{

	Model::Model(string const& path) : gammaCorrection()
	{

		 _modImporter->LoadModel(path, _model);
	}

	void Model::MoveModel(glm::vec3 direction) 
	{
		for (int i = 0; i < _model._meshes.size(); i++)
		{
			_model._meshes[i].SetPosition(direction.x, direction.y, direction.z);
		}
	}

	void Model::ScaleModel(float x, float y, float z) 
	{
		for (int i = 0; i < _model._meshes.size(); i++)
		{
			if (x < 0 || y < 0 || z < 0) 
			{
				x = 0; y = 0; z = 0;
			}
			_model._meshes[i].SetScale(x, y, z);
		}
	}

	void Model::Draw()
	{
		_model.renderer->UpdateProgram(TRS);
		for (unsigned int i = 0; i < _model._meshes.size(); i++)
		{
			_model._meshes[i].Draw();
		}
	}
	void Model::TriggerCollision(Entity* other) { }

}
