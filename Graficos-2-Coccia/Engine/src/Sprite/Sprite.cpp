#include "Sprite.h"

namespace Engine
{	
	Sprite::Sprite(Renderer* renderer, const char* name) : Entity()
	{
		_renderer = renderer;
		//_textureImporter = new TextureImporter();

		//_animation = new Animation();
		_textureImporter.ImportTexture(_renderer, name,_diffuse);
		_textureImporter.ImportTexture(_renderer, name,_specular);
		_vertexSize = sizeof(_vertex);

		_renderer->SetVertexBuffer(_vertexSize, _vertex, _vao, _vbo);
		_renderer->SetIndexBuffer(_vertexSize, _index, _ebo);
		_renderer->SetVertexAttribPointer(false, _modelUniform);
		_renderer->BindTexture2(_diffuse,_specular);
	}

	Sprite::Sprite(Renderer* renderer, const glm::ivec2& tileDimensions) : Entity()
	{
		_renderer = renderer;

		_animation = new Animation();
		_animation->InitSpriteSheet(this, tileDimensions);
	}

	Sprite::~Sprite()
	{
		_renderer->DeleteBuffers(_vao, _vbo, _ebo);

		if (_animation != NULL)
			delete _animation;
		//if (_textureImporter != NULL)
		//	delete _textureImporter;
	}

	void Sprite::InitTexture()
	{
		_vertexSize = sizeof(_vertex);

		//_renderer->CreateBuffers();
		//_renderer->BindBuffers();
		//_renderer->SetVertexSpriteAttribPointer();
		
		_renderer->SetVertexBuffer(_vertexSize, _vertex, _vao, _vbo);
		_renderer->SetIndexBuffer(_vertexSize, _index, _ebo);
		_renderer->SetVertexAttribPointer(false, _modelUniform);
		_renderer->BindTexture2(_diffuse, _specular);


	}
	
	void Sprite::ImportTexture(const char* name)
	{
		//_textureImporter.ImportTexture(_renderer, name, _texture);
		//_textureImporter->ImportTexture(_renderer, name, _textureData);
		
	}

	void Sprite::Draw()
	{
		
		_renderer->SetVertexAttribPointer(false, _modelUniform);
		_renderer->UpdateModel(_generalMatrix.model, _modelUniform);
		_renderer->BindTexture2(_diffuse, _specular);

		//_textureImporter->BindTexture(_textureData._texture);
		_renderer->Draw(_alpha,_vao, _vbo, _ebo, _vertex, _vertexSize, sizeof(_index) / sizeof(float));

		_renderer->DisableTexture();
	}

	void Sprite::DrawAnimation(glm::vec4 uvRect)
	{
		//UpdateUVs
		_vertex[7] =  _uv[0].u; _vertex[8]  = _uv[0].v;
		_vertex[16] = _uv[1].u; _vertex[17] = _uv[1].v;
		_vertex[25] = _uv[2].u; _vertex[26] = _uv[2].v;
		_vertex[34] = _uv[3].u; _vertex[35] = _uv[3].v;

		//Set UV
		_uv[0].u = uvRect.x + uvRect.z; _uv[0].v = uvRect.y + uvRect.w;
		_uv[1].u = uvRect.x + uvRect.z; _uv[1].v = uvRect.y;
		_uv[2].u = uvRect.x; _uv[2].v = uvRect.y;
		_uv[3].u = uvRect.x; _uv[3].v = uvRect.y + uvRect.w;

		_renderer->UpdateModel(_generalMatrix.model, _modelUniform);

		//_renderer->BindTexture(_texture);

		_renderer->Draw(_alpha,_vao, _vbo, _ebo, _vertex, _vertexSize, sizeof(_index) / sizeof(float));

		_renderer->DisableTexture();
	}
	// --------------------------------
	void Sprite::SetColor(ENTITY_COLOR color) { }

	void Sprite::SetColor(float r, float g, float b) { }

	void Sprite::TriggerCollision(Entity* other) { }

	void Sprite::SetAnimation()
	{
		_animation = new Animation(); // para el final te agregamos una lista de animaciones
	}

	Animation* Sprite::GetAnimation()
	{
		return _animation;
	}
}

