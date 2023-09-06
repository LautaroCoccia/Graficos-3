#ifndef MODEL_iMPORTER_H
#define MODEL_iMPORTER_H

#include "../Export/Export.h"
#include "../Renderer/Renderer.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../TextureImporter/stb_image.h"
#include "../3D/Mesh.h"

#include <assimp/include/Importer.hpp>
#include <assimp/include/scene.h>
#include <assimp/include/postprocess.h>
namespace Engine
{
	struct ModelData
	{
		vector <MeshTexture> textures_loaded;
		vector<Mesh> meshes;

		bool hasSpecularMaps;

		Renderer* renderer;
	};

	class EXPORT_API ModelImporter
	{
	private:
		static void processNode(aiNode* node, const aiScene* scene, ModelData& model);
		static Mesh processMesh(aiMesh* mesh, const aiScene* scene, ModelData& model);
		static vector<MeshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName, ModelData& model);

		static unsigned int TextureFromFile(const char* path, const string& directory, bool gamma);

	public:
		static void loadModel(string const& path, bool flipUVs, ModelData& model);

	};

};
#endif // !MODEL_iMPORTER_H

