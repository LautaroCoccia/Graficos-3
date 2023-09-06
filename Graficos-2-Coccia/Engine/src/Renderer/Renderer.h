#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include "..\Export\Export.h"
#include "..\Shader\Shader.h"
#include "..\Camera\Camera.h"
#include "glm\glm\mat4x4.hpp"
using namespace glm;
namespace Engine
{
	struct LightData
	{
		glm::vec3 _color;
		glm::vec3 _position;
		
		glm::vec3 _ambient;
		glm::vec3 _diffuse;
		glm::vec3 _specular;

		int _isActive;
	};
	struct DirectionLightData
	{
		glm::vec3 _direction;
	};

	struct PointLightData
	{
		glm::vec3 _position;

		float _constant;
		float _linear;
		float _quadratic;
	};

	struct SpotlightData
	{
		glm::vec3 _position;
		glm::vec3 _direction;

		float _cutOff;
		float _outerCutOff;

		float _constant;
		float _linear;
		float _quadratic;
	};
	struct Material
	{
		glm::vec3 _ambient;
		glm::vec3 _diffuse;
		glm::vec3 _specular;
		float _shininess;
	};
	enum class TypeOfShape {
		Triangle,
		Quad
	};
	class EXPORT_API Renderer
	{
	private:
		unsigned int _modelInd;
		unsigned int _viewInd;
		unsigned int _projectionInd;
		
		Shader* _shader;
		Camera* _camera;

		unsigned int _VBO = 0; // VertexBufferObject 
		unsigned int _VAO = 0; // VertexArrayObject 
		unsigned int _EBO = 0; // ElementsBufferObject 
	public:
		Renderer();
		~Renderer();
		
		int InitGlew();
		
		void CreateBuffers();
		void BindBuffers();


		void SetVertexShapeAttribPointer();
		void SetVertexSpriteAttribPointer();
		void SetCubeVertexAttribPointer(unsigned int& model);
		void SetVertexMaterialAttribPointer();

		void SetLightVertexArray(unsigned int& vao, unsigned int& vbo);
		void SetLightAttribPointer();

		void SetVertexBuffer(int size, float* vertex, unsigned int &vao, unsigned int &vbo);
		void SetIndexBuffer(int size, unsigned int* index, unsigned int &ebo);
		void SetVertexAttribPointer(bool shape, unsigned int &model);
		void CreateShader();
		void BindTexture(unsigned int& texture);
		void BindTexture2(unsigned int& texture1, unsigned int& texture2);
		void BindTexture3(unsigned int& texture1, unsigned int& texture2, unsigned int& texture3);
		void UpdateProgram(mat4 model);

		void DisableTexture();
		void UpdateLightData(LightData lightData);
		void UpdateDirectLightData(LightData& light, DirectionLightData& directional);
		void UpdatePointLight(LightData& light, PointLightData& point, int i);
		void UpdateSpotLight(LightData& light, SpotlightData& spot, int i);
		void Draw(bool alpha, unsigned int& vao, unsigned int& vbo, unsigned int& ebo, float* vertex, float vertexSize, int vertexCount);
		void DrawCube(bool alpha, unsigned int& vao, unsigned int& vbo, unsigned int& ebo, float* vertex, float vertexSize, int vertexCount);
		
		void UpdateModel(glm::mat4 model, unsigned int updateShape);
		void UpdateMaterial(Material& material);

		void StopShader();
		void DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo);

		//void SetCameraValues(CameraType type, float near, float far, float height, float width);
		//void SetCameraPosition(float x, float y, float z);
		void SetIndex(unsigned int shaderId);
		void UpdateMVP(glm::mat4 model);
		unsigned int GetShader();
		void SetCurrentCamera(Camera* camera);
		void UpdateModelUniform(glm::mat4 modelMatrix, unsigned int shaderId);
	};
}
#endif