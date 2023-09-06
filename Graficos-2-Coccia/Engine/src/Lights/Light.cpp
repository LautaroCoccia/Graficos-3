#include "Light.h"
#include <iostream>
using namespace std;
namespace Engine
{
	Light::Light(Renderer* renderer, glm::vec3 color) 
	{
		_lightData._position = glm::vec3(0, 0, 0);

		_lightData._color = glm::vec3(0, 1, 0);

		_lightData._diffuse = _lightData._color * glm::vec3(0.5f);
		_lightData._ambient = _lightData._diffuse * glm::vec3(0.2f);

		_lightData._specular = { 1.0f, 1.0f, 1.0f };

		_renderer = renderer;

	}
	Light::~Light()
	{
	}
	void Light::SetLightData(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, glm::vec3 lightColor)
	{
		_lightData._color = lightColor;
		_lightData._ambient = ambient;
		_lightData._diffuse = diffuse;
		_lightData._specular = specular;
	}
	void Light::SetPosition(glm::vec3 position)
	{
		_lightData._position = position;
	}
	void Light::Draw(int i)
	{
		//glm::vec3 lightColor = _ambient.color * _ambient.strength;
		_renderer->UpdateLightData(_lightData);
	}
}