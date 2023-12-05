#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>

#include "../Export/Export.h"
#include "../Entity/Entity.h"
#include "../Renderer/Renderer.h"
#include "glm/glm/vec2.hpp"
#include "glm/glm/vec3.hpp"
#include "glm/glm/mat4x4.hpp"
#include <array>

using namespace std;

namespace Engine
{
	struct BoundingBox {
		glm::vec3 min;
		glm::vec3 max;
	};
	struct Vertex
	{
		vec3 Position;
		vec3 Normal;
		vec2 TexCoords;
		vec3 Tangent;
		vec3 Bitangent;
	};

	struct MeshTexture
	{
		unsigned int id;
		string type;
		string path;
	};

	class EXPORT_API Mesh : public Entity
	{
	private:
		unsigned int _vao;
		unsigned int _vbo;
		unsigned int _ebo;
		unsigned int _positionAttrib;
		unsigned int _normalAttrib;
		unsigned int _textureAttrib;

		BoundingBox _boundingBox;
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<MeshTexture> textures;
		Mesh* parent;

		bool _usesSpecularMaps;
		Renderer* _renderer;

		void SetUpMesh();

	public:
		vector<Mesh*> children;
		bool canDraw;
		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<MeshTexture> textures, bool usesSpecularMaps);
		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<MeshTexture> textures, Transform);
		~Mesh();
		void Draw();
		BoundingBox CalculateBoundingBox();
		array<glm::vec3, 8> verticesBoundingBox;
		array<glm::vec3, 8> CalculateVerticesBoundingBox(BoundingBox bbox);
		// --------------------------------
		// Virtual Functions:

		void SetColor(ENTITY_COLOR color);
		void SetColor(float r, float g, float b);
		void TriggerCollision(Entity* other);
	};
}

#endif