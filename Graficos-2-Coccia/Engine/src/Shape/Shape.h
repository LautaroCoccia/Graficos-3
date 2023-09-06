#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include "..\Export\Export.h"
#include "..\Entity\Entity.h"
#include "..\Renderer\Renderer.h"

namespace Engine
{
	class EXPORT_API Shape : public Entity
	{
	private:
		float _triangleVertex[18] = {
			/*Pos*/ -0.1f,  0.0f, 0.0f, /*Color*/ 1.0f, 0.0f, 0.0f,
			/*Pos*/  0.0f,  0.2f, 0.0f, /*Color*/ 1.0f, 0.0f, 0.0f,
			/*Pos*/  0.1f,  0.0f, 0.0f, /*Color*/ 1.0f, 0.0f, 0.0f
		};

		float _quadVertex[24] = {
			/*Pos*/-0.1f,  0.1f, 0.0f, /*Color*/ 1.0f, 0.0f, 0.0f,
			/*Pos*/-0.1f, -0.1f, 0.0f, /*Color*/ 1.0f, 0.0f, 0.0f,
			/*Pos*/ 0.1f, -0.1f, 0.0f, /*Color*/ 1.0f, 0.0f, 0.0f,
			/*Pos*/ 0.1f,  0.1f, 0.0f, /*Color*/ 1.0f, 0.0f, 0.0f
		};
		
		unsigned int _indexTris[3] = {
			0,1,2,
		};

		unsigned int _indexPos[6] = {
			0,1,2,
			3,2,0
		};

		int _vertexSize;
		float* _vertex;

		unsigned int _vao; // Vertex Array Obj
		unsigned int _vbo; // Vertex Buffer Obj
		unsigned int _ebo; // Index Buffer Obj
		
		TypeOfShape _shape;
		unsigned int _modelUniform;
		Renderer* _renderer;

	public:
		Shape(Renderer* renderer);
		~Shape();
		void InitShape(TypeOfShape type);
		void Draw();

		void SetColor(ENTITY_COLOR color) ;
		void SetColor(float r, float g, float b) ;
		void TriggerCollision(Entity* other);
	};
}

#endif

