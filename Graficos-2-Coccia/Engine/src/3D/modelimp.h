#ifndef MODELIMP_H
#define MODELIMP_H

#include <glm/glm.hpp>
//#include "../../TextureImporter/stb_image.h"
#include <assimp/include/scene.h>
#include <assimp/include/postprocess.h>
#include <assimp/include/Importer.hpp>

#include "mesh.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "../TextureImporter/TextureImporter.h"

using namespace std;

namespace Engine
{
	class EXPORT_API ModelImp : public Entity
	{
	private:
		int _width = 0;
		int _height = 0;
		bool _transparency;
		
		vector<Texture> _textures_loaded;
		vector<Mesh> _meshes;
		string _path;

		const char* _modelTexture;
		string _directory;

		void LoadModel(string path);
		void ProcessNode(aiNode* node, const aiScene* scene);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
		vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);

		TextureImporter* _texImporter = NULL;

		Renderer* _renderer;

	public:
		ModelImp(string path, Renderer* renderer);
		~ModelImp();
		//void MoveModel(glm::vec3 direction);
		//void ScaleModel(float x, float y, float z);
		//void RotateModelX(float x);
		//void RotateModelY(float y);
		//void RotateModelZ(float z);
		//void SetModelPath(string path);
		//void SetTexturePath(const char* texturePath);
		void Draw();

		// --------------------------------
		// Virtual Functions:

		void SetColor(ENTITY_COLOR color);
		void SetColor(float r, float g, float b);
		void TriggerCollision(Entity* other);
	};
}

#endif