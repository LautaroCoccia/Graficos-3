#ifndef SPRITE_H
#define SPRITE_H

#include "..\Export\Export.h"
#include "..\Entity\Entity.h"
#include "..\Renderer\Renderer.h"
#include "..\Animation\Animation.h"
#include "..\TextureImporter\TextureImporter.h"

namespace Engine
{
	struct EXPORT_API UVs
	{
		float u;
		float v;
	};

	class EXPORT_API Sprite : public Entity
	{
		float _vertex[36]
		{
			// positions          // colors					// texture coords
			 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top right
			 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 0.0f,   // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f, 1.0f,   0.0f, 1.0f    // top left
		};

		//float _vertexes[32]
		//{
		//	// positions          // colors					// texture coords
		//	 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		//	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		//	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		//	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
		//};
		float _borderColor[4]
		{
			1.0f, 1.0f, 0.0f, 1.0f
		};

		unsigned int _index[6] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};
		bool _alpha = false;
		unsigned int _vao; // Vertex Array Obj
		unsigned int _vbo; // Vertex Buffer Obj
		unsigned int _ebo; // Index Buffer Obj

		int _vertexSize;
		unsigned int _diffuse;
		unsigned int _specular;
		//unsigned int _texture;

		unsigned int _modelUniform;
		
		UVs _uv[4];

		Animation* _animation; // Acá se podria poner una lista para asi tener mas de 1 animacion
		TextureImporter _textureImporter;
		//TextureData _textureData;
		Renderer* _renderer;
	public:
		Sprite(Renderer* renderer, const char* name);
		Sprite(Renderer* renderer, const glm::ivec2& tileDimensions);
		~Sprite();

		void InitTexture();
		void ImportTexture(const char*name);
		void Draw();
		void DrawAnimation(glm::vec4 uvRect);
		void SetColor(ENTITY_COLOR color);
		void SetColor(float r, float g, float b);
		void TriggerCollision(Entity* other);

		void SetAnimation();
		Animation* GetAnimation();
	};
}
#endif