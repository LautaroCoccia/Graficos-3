#include "Cube.h"
#include <iostream>
using namespace std;
namespace Engine
{
	Cube::Cube(const char* filePath) : Entity()
	{
		_renderer = _renderer->_staticRenderer;

		//TI.ImportTexture(_renderer, filePath, _diffuse);
		if (_data._nrChannels == 4)
			_alpha = true;

		_vertexSize = sizeof(_vertices);

		//_renderer->SetVertexSpriteAttribPointer();

		_renderer->SetVertexBuffer(_vertexSize, _vertices, _vao, _vbo);
		_renderer->SetIndexBuffer(_vertexSize, _index, _ebo);
		
		_renderer->SetCubeVertexAttribPointer(_modelUniform);
		
		

		/*for (int i = 0; i < 6; i++)
		{
			cube[i] = new Sprite(renderer);
			cube[i]->InitTexture();
			cube[i]->ImportTexture(filePath);
			cube[i]->SetPosition(facesPositions[i]);
			cube[i]->SetRotation(facesRotations[i]);
		}*/
	}
	Cube::Cube() : Entity()
	{
		_data._width = 0;
		_data._height = 0;
		_data._nrChannels = 0;
		_data._diffuse = 0;
	}
	Cube::Cube(std::string name, const char* filePath) : Entity()
	{
		_data = TI.ImportTexture(filePath);
		if (_data._nrChannels == 4)
			_alpha = true;

		//_material.color = glm::vec4(1.0, 1.0, 1.0, 1.0);
		//_material.ambient = glm::vec3(1.0, 1.0, 1.0);
		//_material.shininess = 32;
	}
	Cube::~Cube()
	{
		_renderer->DeleteBuffers(_vao, _vbo, _ebo);
		//for (int i = 5; i >= 6; i--)
		//{
		//	if (cube[i] != NULL)
		//		delete cube[i];
		//}
	}
	void Cube::UpdatePosition()
	{
		//for (int i = 0; i < 6; i++)
		//{
		//	cube[i]->SetPosition(facesPositions[i] + _transform.position);
		//}
	}

	void Cube::Draw()
	{
		//for (int i = 0; i < 6; i++)
		//{
		//	cube[i]->Draw();
		//}
		//_textureImporter->BindTexture(_textureData._texture);

		
		_renderer->BindTexture(_data._diffuse);
		//_renderer->SetCubeVertexAttribPointer(_modelUniform);

		_renderer->UpdateModel(_generalMatrix.model, _modelUniform);
		_renderer->Draw(_alpha,_vao, _vbo, _ebo, _vertices, _vertexSize, sizeof(_index) / sizeof(float));
		
		_renderer->DisableTexture();
	}
	void Cube::TriggerCollision(Entity* other)
	{
		if (!other->GetStaticState())
		{
			glm::vec3 newPos = _transform.position;
			ReturnToPrevPosition();
			newPos -= _transform.position;

			other->SetPosition(other->_transform.position + newPos);
		}
		else
		{
			ReturnToPrevPosition();
		}
	}
}
