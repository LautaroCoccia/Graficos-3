#include "Model.h"
#include <glm/ext/matrix_transform.hpp>
#include <iostream>
using namespace std;
namespace Engine
{

	Model::Model( string const& path, bool flipUVs, bool gamma) 
	{
		_model.renderer = _model.renderer->_staticRenderer;

		ModelImporter::loadModel(path, flipUVs, _model);
	}

	void Model::MoveModel(glm::vec3 direction) 
	{
		_transform.position = direction;
		_generalMatrix.translate = translate(mat4(1.0f), _transform.position);

		for (int i = 0; i < _model.meshes.size(); i++)
		{
			_model.meshes[i]->SetPosition(direction.x, direction.y, direction.z);
			//cout << "Position: " << _model.meshes[0]->GetPosition().x << " " << _model.meshes[0]->GetPosition().y << " " << _model.meshes[0]->GetPosition().z << endl;
		}
		UpdateMatrix();
	}
	//void Model::SetMeshPosition(vec3 pos, int meshIndex)
	//{
	//
	//}
	void Model::ScaleModel(float x, float y, float z) 
	{
		for (int i = 0; i < _model.meshes.size(); i++)
		{
			if (x < 0 || y < 0 || z < 0) 
			{
				x = 0; y = 0; z = 0;
			}
			//_model.meshes[i]->SetScale(x, y, z);
		}
	}

	void Model::Draw()
	{
		//_renderer->UpdateModelUniform(_generalMatrix.model, _renderer->GetShader());
		_renderer->UpdateProgram(_generalMatrix.model);
		for (unsigned int i = 0; i < _model.meshes.size(); i++)
		{
			_model.meshes[i]->Draw();
		}
	}
	void Model::TriggerCollision(Entity* other) { }

}
