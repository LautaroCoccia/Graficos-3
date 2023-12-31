#include "ModelImporter.h"

#include <iostream>
#include "GL/glew.h"

string directory;

using namespace std;
using namespace glm;
namespace Engine
{
	void ModelImporter::loadModel(string const& path, bool flipUVs, ModelData& model)
	{
		stbi_set_flip_vertically_on_load(flipUVs);
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals  | aiProcess_CalcTangentSpace);
		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
			return;
		}
		directory = path.substr(0, path.find_last_of('/'));

		processNode(scene->mRootNode, scene, model);
	}

	void ModelImporter::processNode(aiNode* node, const aiScene* scene, ModelData& model)
	{
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			model.meshes.push_back(processMesh(mesh, scene, model));
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			processNode(node->mChildren[i], scene, model);
		}
	}

	Mesh ModelImporter::processMesh(aiMesh* mesh, const aiScene* scene, ModelData& model)
	{
		vector<Vertex> vertices;
		vector<unsigned int> indices;
		vector<MeshTexture> textures;

		for (unsigned int i = 0; i < mesh->mNumVertices; i++)
		{
			Vertex vertex;
			glm::vec3 vector;

			vector.x = mesh->mVertices[i].x;
			vector.y = mesh->mVertices[i].y;
			vector.z = mesh->mVertices[i].z;
			vertex.Position = vector;

			if (mesh->HasNormals())
			{
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.Normal = vector;
			}
			if (mesh->mTextureCoords[0])
			{
				glm::vec2 vec;
				vec.x = mesh->mTextureCoords[0][i].x;
				vec.y = mesh->mTextureCoords[0][i].y;
				vertex.TexCoords = vec;

				vector.x = mesh->mTangents[i].x;
				vector.y = mesh->mTangents[i].y;
				vector.z = mesh->mTangents[i].z;
				//vertex.Tangent = vector;

				vector.x = mesh->mBitangents[i].x;
				vector.y = mesh->mBitangents[i].y;
				vector.z = mesh->mBitangents[i].z;
				//vertex.Bitangent = vector;
			}
			else
			{
				vertex.TexCoords = glm::vec2(0.0f, 0.0f);
			}
			vertices.push_back(vertex);
		}
		for (unsigned int i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (unsigned int j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		vector<MeshTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", model);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		vector<MeshTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", model);
		if (specularMaps.empty()) model.hasSpecularMaps = false;
		else model.hasSpecularMaps = true;

		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

		// NORMAL USES HEIGHT INSTEAD OF NORMALS
		vector<MeshTexture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal", model);
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

		// HEIGHT USES AMBIENT INSTEAD OF HEIGHT 
		vector<MeshTexture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height", model);
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
		//return Mesh(vertices, indices, textures, model.hasSpecularMaps, model.renderer);
		return Mesh(vertices, indices, textures, model.hasSpecularMaps, model.renderer);
	}

	vector<MeshTexture> ModelImporter::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName, ModelData& model)
	{
		vector<MeshTexture> textures;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			//cout << str.C_Str() << endl;
			bool skip = false;
			for (unsigned int j = 0; j < model.textures_loaded.size(); j++)
			{
				if (std::strcmp(model.textures_loaded[j].path.data(), str.C_Str()) == 0)
				{
					textures.push_back(model.textures_loaded[j]);
					skip = true;
					break;
				}
			}
			if (!skip)
			{

				MeshTexture texture;
				texture.id = TextureFromFile(str.C_Str(), directory, false);
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
				model.textures_loaded.push_back(texture);
			}
		}
		return textures;
	}

	unsigned int ModelImporter::TextureFromFile(const char* path, const string& directory, bool gamma)
	{
		string filename = string(path);
		filename = directory + '/' + filename;

		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width;
		int height;
		int nrComponents;

		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
			{
				format = GL_RED;
			}
			else if (nrComponents == 3)
			{
				format = GL_RGB;
			}
			else if (nrComponents == 4)
			{
				format = GL_RGBA;
			}

			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			stbi_image_free(data);
		}
		else
		{
			cout << "Texture failed to load at path: " << path << endl;
			stbi_image_free(data);
		}
		return textureID;
	}
}

