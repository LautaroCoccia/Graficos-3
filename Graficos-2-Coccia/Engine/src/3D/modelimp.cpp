#include "modelimp.h"

#include "GL/glew.h"

using namespace Engine;

ModelImp::ModelImp(string path, Renderer* renderer) : Entity()
{
    _texImporter = new TextureImporter();
    _renderer = renderer;

    LoadModel(path);
}

ModelImp::~ModelImp()
{
    if (_texImporter != NULL)
    {
        delete _texImporter;
        _texImporter = NULL;
    }
}

//void ModelImp::MoveModel(glm::vec3 direction)
//{
//    for (int i = 0; i < _meshes.size(); i++)
//    {
//        _meshes[i].Translate(direction.x, direction.y, direction.z);
//    }
//}
//
//void ModelImp::ScaleModel(float x, float y, float z)
//{
//    for (int i = 0; i < _meshes.size(); i++)
//    {
//        if (x < 0 || y < 0 || z < 0)
//        {
//            x = 0;y = 0;z = 0;
//        }
//        _meshes[i].Scale(x, y, z);
//    }
//}
//
//void ModelImp::RotateModelX(float x)
//{
//    for (int i = 0; i < _meshes.size(); i++)
//    {
//        _meshes[i].RotateX(x);
//    }
//}
//
//void ModelImp::RotateModelY(float y)
//{
//    for (int i = 0; i < _meshes.size(); i++)
//    {
//        _meshes[i].RotateY(y);
//    }
//}
//
//void ModelImp::RotateModelZ(float z)
//{
//    for (int i = 0; i < _meshes.size(); i++)
//    {
//        _meshes[i].RotateZ(z);
//    }
//}

void ModelImp::Draw()
{
    for (unsigned int i = 0; i < _meshes.size(); i++)
    {
        _meshes[i].Draw();
    }
}


// ------------------------------
// Private Func

void ModelImp::LoadModel(string path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_CalcTangentSpace);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
        return;
    }
    _directory = path.substr(0, path.find_last_of('/'));

    if(scene)
        ProcessNode(scene->mRootNode, scene);
}

void ModelImp::ProcessNode(aiNode* node, const aiScene* scene)
{
    std::cout << "Entro en ProcessNode!!!" << std::endl;
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        _meshes.push_back(ProcessMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh ModelImp::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) 
    {
        Vertex vertex;
        //Procesar las posiciones, normales y uvs de los vertices de cada una de la mesh
        //Necesitmaos un vector temporal para los datos de Assimp, eso se hace ya que Assimp tiene sus propios tipos de datos para vectores, matrices, etc.
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;

        //Aca hacemos lo mismo que en el paso anterior solo que con los datos de los vectores normales
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
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) 
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = LoadMaterialTextures(material, aiTextureType_HEIGHT, "normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = LoadMaterialTextures(material, aiTextureType_AMBIENT, "height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    std::cout << "Entro en ProcessMesh!!!" << std::endl;

    return Mesh(vertices, indices, textures, _renderer);
}

vector<Texture> ModelImp::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName) 
{
    vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (unsigned int j = 0; j < _textures_loaded.size(); j++)
        {
            if (std::strcmp(_textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(_textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if (!skip) 
        {
            Texture texture;
            //texture.id = TextureFromFile(str.C_Str(), this->_directory, false);
            texture.id = _texImporter->TextureFromFile(str.C_Str(), this->_directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            //texture.path = _modelTexture;
            textures.push_back(texture);
            _textures_loaded.push_back(texture);
        }
    }

    std::cout << "Entro en LoadMaterialTextures!!!" << std::endl;

    return textures;
}

// --------------------------------
// Virtual Functions:

void ModelImp::SetColor(ENTITY_COLOR color) { }
void ModelImp::SetColor(float r, float g, float b) { }
void ModelImp::TriggerCollision(Entity* other) { }