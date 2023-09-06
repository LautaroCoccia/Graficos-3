#include "Cubo.h"

namespace Engine
{
    const int _vertex = 192;
    float _vertices[_vertex] = {

        // positions          // normal                // texture coords
         0.5f,  0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // top left 

         0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,

         0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 1.0f,

        -0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0,   1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   -1.0f, 0.0f, 0.0,   1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0,   0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   -1.0f, 0.0f, 0.0,   0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0,   1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0,   1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0,   0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0,   0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0,   1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0,   1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0,   0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0,   0.0f, 1.0f
    };
    const int _indexLength = 36;
    unsigned int _index[_indexLength] = {
        0, 1, 3, // first triangle
        1, 2, 3,  // second triangle
        4, 5, 7,
        5, 6, 7,
        8, 9, 11,
        9, 10, 11,
        12, 13, 15,
        13, 14, 15,
        16, 17, 19,
        17, 18, 19,
        20, 21, 23,
        21, 22, 23
    };
	Cubo::Cubo(const char* filePath, Renderer* renderer) : Entity()
	{
		_renderer = renderer;

		//TI.ImportTexture(_renderer, filePath, _);

		_vertexSize = sizeof(_vertices);

		_renderer->SetVertexBuffer(_vertexSize, _vertices, _vao, _vbo);
		_renderer->SetIndexBuffer(_vertexSize, _index, _ebo);
		
		_renderer->SetCubeVertexAttribPointer(_modelUniform);
        //_renderer->BindTexture(_data._diffuse);

		//_renderer->SetVertexAttribPointer(false, _modelUniform);

		//material.color = glm::vec4(1.0, 1.0, 1.0, 1.0);
		//material.ambient = glm::vec3(1.0, 1.0, 1.0);
		//material.diffuse = glm::vec3(1.0, 1.0, 1.0);
		//material.shininess = 1;
		//material.specular = glm::vec3(1.0, 1.0, 1.0);

        _material._ambient = glm::vec3(1.0, 1.0, 1.0);
        _material._diffuse = glm::vec3(1, 1, 1);
        _material._specular = glm::vec3(0.1, 0.1f, 0.1f);
        _material._shininess = 32;
	}
    Cubo::Cubo(const char* diffuse, const char* specular, Renderer* renderer) : Entity()
    {
        _renderer = renderer;

        TI.ImportTexture(_renderer, diffuse, _diffuseMap);
        if(specular != NULL)
            TI.ImportTexture(_renderer, specular, _specularMap);
        else 
            TI.ImportTexture(_renderer, diffuse, _specularMap);
        
        _vertexSize = sizeof(_vertices);

        _renderer->SetVertexBuffer(_vertexSize, _vertices, _vao, _vbo);
        _renderer->SetIndexBuffer(_vertexSize, _index, _ebo);

        _renderer->SetCubeVertexAttribPointer(_modelUniform);
        _renderer->BindTexture2(_diffuseMap, _specularMap);

        _renderer->SetVertexAttribPointer(false, _modelUniform);

        //material.color = glm::vec4(1.0, 1.0, 1.0, 1.0);
        //material.ambient = glm::vec3(1.0, 1.0, 1.0);
        //material.diffuse = glm::vec3(1.0, 1.0, 1.0);
        //material.shininess = 1;
        //material.specular = glm::vec3(1.0, 1.0, 1.0);

        //_material._ambient = glm::vec3(1.0, 1.0, 1.0);
        //_material._diffuse = glm::vec3(1, 1, 1);
        //_material._specular = glm::vec3(0.1, 0.1f, 0.1f);
        //_material._shininess = 32;
    }
    Cubo::Cubo(const char* diffuse, const char* specular, const char* emission, Renderer* renderer) : Entity()
    {
        _renderer = renderer;

        TI.ImportTexture(_renderer, diffuse, _diffuseMap);
        if (specular != NULL)
        {
            TI.ImportTexture(_renderer, specular, _specularMap);
        }
        else
        {
            TI.ImportTexture(_renderer, diffuse, _specularMap);
        }
        TI.ImportTexture(_renderer, emission, _emissionMap);
        

        _vertexSize = sizeof(_vertices);

        _renderer->SetVertexBuffer(_vertexSize, _vertices, _vao, _vbo);
        _renderer->SetIndexBuffer(_vertexSize, _index, _ebo);

        _renderer->SetCubeVertexAttribPointer(_modelUniform);
        //_renderer->BindTexture2(_diffuseMap, _specularMap);
        _renderer->BindTexture3(_diffuseMap, _specularMap, _emissionMap);

        _renderer->SetVertexAttribPointer(false, _modelUniform);
    }
    void Cubo::SetEmission(const char* emmision)
    {
        TI.ImportTexture(_renderer, emmision, _emissionMap);
        _vertexSize = sizeof(_vertices);

        _renderer->SetVertexBuffer(_vertexSize, _vertices, _vao, _vbo);
        _renderer->SetIndexBuffer(_vertexSize, _index, _ebo);

        _renderer->SetCubeVertexAttribPointer(_modelUniform);
        _renderer->BindTexture(_emissionMap);

        _renderer->SetVertexAttribPointer(false, _modelUniform);
    }
    /*Cubo::Cubo(const char* filePath, Renderer* renderer) : Entity()
    {
        _renderer = renderer;

        TI.ImportTexture(_renderer, filePath, _data);
        if (_data._nrChannels == 4)
            _alpha = true;

        _vertexSize = sizeof(_vertices);

        //_renderer->CreateBuffers();
        //_renderer->BindBuffers();

        _renderer->SetVertexBuffer(_vertexSize, _vertices, _vao, _vbo);
        _renderer->SetIndexBuffer(_vertexSize, _index, _ebo);

        _renderer->SetCubeVertexAttribPointer(_modelUniform);
        _renderer->BindTexture(_data._diffuse);
        //_renderer->SetVertexAttribPointer(false, _modelUniform);

        //material.color = glm::vec4(1.0, 1.0, 1.0, 1.0);
        //material.ambient = glm::vec3(1.0, 1.0, 1.0);
        //material.diffuse = glm::vec3(1.0, 1.0, 1.0);
        //material.shininess = 1;
        //material.specular = glm::vec3(1.0, 1.0, 1.0);

        _material._ambient = glm::vec3(1.0, 1.0, 1.0);
        _material._diffuse = glm::vec3(1, 1, 1);
        _material._specular = glm::vec3(0.1, 0.1f, 0.1f);
        _material._shininess = 32;
    }*/
    void Cubo::SetMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
    {
        _material._ambient = ambient;
        _material._diffuse = diffuse;
        _material._specular = specular;
        _material._shininess = shininess;

        _renderer->UpdateMaterial(_material);
        //glm::vec3 ambient = glm::vec3(1, 1, 1);
        //glm::vec3 diffuse = glm::vec3(0.1, 0.5f, 0.31f);
        //glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
        //float shininess = 256;
    }
	void Cubo::Draw()
	{
	    _renderer->BindTexture2(_diffuseMap, _specularMap);
        _renderer->UpdateMaterial(_material);
		_renderer->UpdateModel(_generalMatrix.model, _modelUniform);
		//_renderer->BindTexture2(_diffuseMap, _specularMap);

		//_renderer->SetCubeVertexAttribPointer(_modelUniform);
		_renderer->Draw(_alpha,_vao, _vbo, _ebo, _vertices, _vertexSize, sizeof(_index) / sizeof(float));

		_renderer->DisableTexture();
	}
	void Cubo::TriggerCollision(Entity* other) { }

}