#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>

#include "../Export/Export.h"
#include "../Renderer/Renderer.h"
#include "glm/glm/vec2.hpp"
#include "glm/glm/vec3.hpp"
#include "glm/glm/mat4x4.hpp"
using namespace std;

namespace Engine
{
	struct Vertex
	{
		glm::vec3 Position;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
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

		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<MeshTexture> textures;
		bool _usesSpecularMaps;
		Renderer* _renderer;

		void SetUpMesh();

	public:

		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<MeshTexture> textures, bool usesSpecularMaps, Renderer* renderer);
		~Mesh();
		void Draw();

		// --------------------------------
		// Virtual Functions:

		void SetColor(ENTITY_COLOR color);
		void SetColor(float r, float g, float b);
		void TriggerCollision(Entity* other);
	};
}

#endif