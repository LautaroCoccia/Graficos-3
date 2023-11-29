#ifndef CUBE_H
#define CUBE_H

#include "..\Entity\Entity.h"
#include "..\Sprite\Sprite.h"
#include "../TextureImporter/TextureImporter.h"

namespace Engine
{

	class EXPORT_API Cube : public Entity
	{
		/*Sprite* cube[6];
		vec3 facesPositions[6] = {
			vec3(0.0f, 0.0f, 0.5f),
			vec3(0.0f, 0.0f, -0.5f),
			vec3(0.5f, 0.0f, 0.0f),
			vec3(-0.5f, 0.0f, 0.0f),
			vec3(0.0f, 0.5f, 0.0f),
			vec3(0.0f, -0.5f, 0.0f)
		};
		vec3 facesRotations[6] = {
			vec3(0.0f, 0.0f, 0.0f),
			vec3(0.0f, 0.0f, 0.0f),
			vec3(0.0f, 90.0f, 0.0f),
			vec3(0.0f, -90.0f, 0.0f),
			vec3(90.0f, 0.0f, 0.0f),
			vec3(-90.0f, 0.0f, 0.0f)
		};*/
        static const int _vertex = 192;
        float _vertices[_vertex] = {

            // positions          // normal                // texture coords
             0.5f,  0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 1.0f, // top right
             0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f,  // top left 

             0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,

             0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 0.0f,
             0.5f,  0.5f, -0.5f,   0.0f, 0.0f, -1.0f,   0.0f, 1.0f,

            -0.5f, -0.5f, -0.5f,   -1.0f, 0.0f, 0.0,   1.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,   -1.0f, 0.0f, 0.0,   1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,   -1.0f, 0.0f, 0.0,   0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,   -1.0f, 0.0f, 0.0,   0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0,   1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,   0.0f, 1.0f, 0.0,   1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0,   0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0,   0.0f, 1.0f,

            -0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0,   1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,   0.0f, -1.0f, 0.0,   1.0f, 0.0f,
             0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0,   0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0,   0.0f, 1.0f
        };
        static const int _indexLength = 36;
        unsigned int _index[_indexLength] = {
            0, 1, 3, // first triangle
            1, 2, 3,  // second triangle
            4, 5, 7,
            5, 6, 7,
            8, 9, 11,
            9, 10, 11,
            12, 13, 15,
            13, 14, 15,
            16, 17, 19,
            17, 18, 19,
            20, 21, 23,
            21, 22, 23
        };
        TextureImporter TI;
        TextureData _data;
        bool _alpha = false;
        Material _material;
        int _vertexSize;
        unsigned int _modelUniform;
        unsigned int _diffuseMap;
        unsigned int _specularMap;
        unsigned int _emissionMap;
        
        unsigned int _vao; // Vertex Array Obj
        unsigned int _vbo; // Vertex Buffer Obj
        unsigned int _ebo; // Index Buffer Obj
    public:
        Cube(const char* filePath);
        Cube();
        Cube(std::string name, const char* filePath);
        // Cube(const char* filePath, Renderer* renderer);
        ~Cube();
        void SetMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
        void UpdatePosition();
        void Draw();
		void TriggerCollision(Entity* other) override;
	};
}	
#endif // !CUBE_H


