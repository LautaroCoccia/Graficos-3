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
struct aiNode;
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
		unsigned char* pixelData;
		int width;
		int height;
		int nrChannels;
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
		int indexCount;
		BoundingBox _boundingBox;
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<MeshTexture> textures;
		Mesh* parent;
		aiNode* myself;
		bool _usesSpecularMaps;
		Renderer* _renderer;

		void SetUpMesh();

	public:
		string name;
		bool imParent;
		vector<Mesh*> children;
		bool canDraw;
		Mesh();
		Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<MeshTexture> textures, bool usesSpecularMaps);
		~Mesh();
		void CreateMesh(float* vertices, uint* indices, uint numOfVertices, uint numOfIndices);

		void SetNode(aiNode* _myself);
		aiNode* GetNode();
		void SetParent(Mesh* _parent);
		Mesh* GetParent();
		void AddMeshSon(Mesh* newChildren);
		void SetPos(vec3 pos);
		void SetRotX(float x);
		void SetRotY(float y);
		void SetRotZ(float z);

		void Scale(float x, float y, float z);
		void UpdateSonPos();
		void UpdateSonsRotX();
		void UpdateSonsRotY();
		void UpdateSonsRotZ();
		void UpdateSonScale();

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