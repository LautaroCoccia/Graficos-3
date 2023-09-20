#ifndef MODEL_iMPORTER_H
#define MODEL_iMPORTER_H



#include <assimp/include/Importer.hpp>
#include <assimp/include/scene.h>
#include <assimp/include/postprocess.h>
#include "..\3D\Model.h"
#include "../3D/Mesh.h"



#include "../TextureImporter/TextureImporter.h"

namespace Engine
{


	class EXPORT_API ModelImporter
	{
	private:

		void ProcessNode(aiNode* node, const aiScene* scene,Model::ModelData model);
		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene,Model::ModelData model);
		vector<MeshTexture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName, Model::ModelData model);

		TextureImporter* _texImporter = NULL;

		Renderer* _renderer;

	public:
		Model::ModelData LoadModel(string const& path, Model::ModelData model);
	};

};
#endif // !MODEL_iMPORTER_H

