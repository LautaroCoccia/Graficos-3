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
        static const int _vertex = 288;
        float _vertices[_vertex] = {
            //Position              //Normal            //UV       
            //-----------------
            -0.5f, -0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
             0.5f,  0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  	0.0f,  0.0f, -1.0f,    0.0f, 1.0f,

            -0.5f, -0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    0.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  	0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  	0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,    0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  	0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  	0.0f,  0.0f,  1.0f,    0.0f, 1.0f,

            -0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f,    0.0f, 1.0f,

             0.5f,  0.5f,  0.5f,  	1.0f,  0.0f,  0.0f,    0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  	1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  	1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
             0.5f, -0.5f, -0.5f,  	1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  	1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  	1.0f,  0.0f,  0.0f,    0.0f, 1.0f,

            -0.5f, -0.5f, -0.5f,  	0.0f, -1.0f,  0.0f,    0.0f, 1.0f,
             0.5f, -0.5f, -0.5f,  	0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
             0.5f, -0.5f,  0.5f,  	0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
             0.5f, -0.5f,  0.5f,  	0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  	0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  	0.0f, -1.0f,  0.0f,    0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  	0.0f,  1.0f,  0.0f,    0.0f, 1.0f,
             0.5f,  0.5f, -0.5f,  	0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
             0.5f,  0.5f,  0.5f,  	0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
             0.5f,  0.5f,  0.5f,  	0.0f,  1.0f,  0.0f,	   1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  	0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  	0.0f,  1.0f,  0.0f,    0.0f, 1.0f
        };
        static const int _indexLength = 36;
        unsigned int _index[_indexLength] = {
            0, 1, 2,
            3, 4, 5,
            6, 7, 8,
            9, 10, 11,
            12, 13, 14,
            15, 16, 17,
            18, 19, 20,
            21, 22, 23,
            24, 25, 26,
            27, 28, 29,
            30, 31, 32,
            33, 34, 35
        };
        TextureImporter TI;
        TextureData _data;
        bool _alpha = false;
        Renderer* _renderer;
        int _vertexSize;
        unsigned int _modelUniform;
        unsigned int _vao; // Vertex Array Obj
        unsigned int _vbo; // Vertex Buffer Obj
        unsigned int _ebo; // Index Buffer Obj
    public:
        Cube(const char* filePath, Renderer* renderer);
       // Cube(const char* filePath, Renderer* renderer);
        ~Cube();
		void UpdatePosition();
        void Draw();
		void TriggerCollision(Entity* other) override;
	};
}	
#endif // !CUBE_H


