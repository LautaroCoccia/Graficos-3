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
		
		for (int i = 0; i < _model.meshes.size(); i++)
		{
			_model.meshes[i]->SetPos(vec3(direction.x, direction.y, direction.z));
			//cout << "Position: " << _model.meshes[0]->GetPosition().x << " " << _model.meshes[0]->GetPosition().y << " " << _model.meshes[0]->GetPosition().z << endl;
		}
		_generalMatrix.translate = translate(mat4(1.0f), _transform.position);
		UpdateMatrix();
	}
	void Model::SetMeshScale(float x, float y, float z, int index)
	{
		if (index == 0)
		{
			_transform.localScale = { x, y, z };
			_generalMatrix.scale = glm::scale(glm::mat4(1.0f), _transform.localScale);
			//structure.meshes[index]->Scale(x, y, z);

			UpdateMatrix();
		}
		if (_model.meshes[index] != NULL)
			_model.meshes[index]->SetScale(x, y, z);

	}
	void Model::SetMeshPosition(float x, float y, float z, int index)
	{
		_transform.position = { x, y, z };
		_generalMatrix.translate = glm::translate(mat4(1.0f), _transform.position);
		_model.meshes[index]->SetPos(vec3(x, y, z));
		cout << _model.meshes[index]->name.c_str()<< " index "<< index << endl;
		UpdateMatrix();
		
	}
	void Model::SetMeshRotX(float x, int indexMesh) {
		_transform.rotation.x = x;
		_generalMatrix.rotateX = glm::rotate(glm::mat4(1.0f), glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
		_model.meshes[indexMesh]->SetRotationX(x);

		UpdateMatrix();
		//UpdateTransformsData();
	}

	void Model::SetMeshRotY(float y, int indexMesh) {
		_transform.rotation.y = y;
		_generalMatrix.rotateY = glm::rotate(glm::mat4(1.0f), glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
		_model.meshes[indexMesh]->SetRotationY(y);

		UpdateMatrix();
		//UpdateTransformsData();
	}

	void Model::SetMeshRotZ(float z, int indexMesh) {
		_transform.rotation.z = z;
		_generalMatrix.rotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
		_model.meshes[indexMesh]->SetRotationZ(z);

		UpdateMatrix();
		//UpdateTransformsData();
	}

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
			//if(i<4)
				_model.meshes[i]->Draw();
		}
	}
	void Model::TriggerCollision(Entity* other) { }

}
