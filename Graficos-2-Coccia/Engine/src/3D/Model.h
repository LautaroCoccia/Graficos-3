#ifndef MODEL_H
#define MODEL_H

//#include <glm/glm.hpp>

#include "../Entity/Entity.h"
#include "../Export/Export.h"
#include "../ModelImporter/ModelImporter.h"
#include "../Renderer/Renderer.h"
#include "../3D/Mesh.h"

using namespace std;

namespace Engine
{
	class EXPORT_API Model : public Entity
	{
	private:
		ModelImporter* _modImporter= NULL;
		bool gammaCorrection;
		
	public:
		struct ModelData
		{
			int _width = 0;
			int _height = 0;
			bool _transparency;

			vector<MeshTexture> _textures_loaded;
			vector<Mesh> _meshes;
			string _path;

			const char* _modelTexture;
			string _directory;

			Renderer* renderer;
		};
		ModelData _model;
		Model(string const& path);

		void MoveModel(glm::vec3 direction);
		void ScaleModel(float x, float y, float z);

		void Draw();
		void TriggerCollision(Entity* other);
	};
}
#endif 