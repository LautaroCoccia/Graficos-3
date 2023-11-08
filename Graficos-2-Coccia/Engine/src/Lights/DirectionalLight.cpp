#include "DirectionalLight.h"
namespace Engine
{
	DirectionalLight::DirectionalLight(glm::vec3 color, glm::vec3 direction) : Light(color)
	{
		SetDirection(direction);
	}
	DirectionalLight::~DirectionalLight()
	{

	}

	void DirectionalLight::Draw(int i)
	{
		_renderer->UpdateDirectLightData(_lightData, _directionData);
	}
	void DirectionalLight::SetDirection(glm::vec3 direction)
	{
		_directionData._direction = direction;
	}
}