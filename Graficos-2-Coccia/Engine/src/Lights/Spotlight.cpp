#include "Spotlight.h"
namespace Engine
{
	Spotlight::Spotlight(Renderer* renderer, glm::vec3 color, glm::vec3 position, glm::vec3 direction) : Light(renderer, color)
	{
		_spotData._position = position;
		_spotData._direction = direction;

		_spotData._cutOff = glm::cos(glm::radians(12.5f));
		_spotData._outerCutOff = glm::cos(glm::radians(17.5f));

		_spotData._constant = 1.0f;
		_spotData._linear = 0.09f;
		_spotData._quadratic = 0.032f;
	}

	Spotlight::~Spotlight()
	{

	}

	void Spotlight::Draw(int i)
	{
		_renderer->UpdateSpotLight(_lightData, _spotData, i);
	}

	glm::vec3 Spotlight::GetPosition()
	{
		return _spotData._position;
	}

	glm::vec3 Spotlight::GetDirection()
	{
		return _spotData._direction;
	}

	void Spotlight::SetPosition(glm::vec3 position)
	{
		_spotData._position = position;
	}

	void Spotlight::SetDirection(glm::vec3 direction)
	{
		_spotData._direction = direction;
	}

	void Spotlight::SetSpotValues(float constant, float linear, float quadratic)
	{
		_spotData._constant = constant;
		_spotData._linear = linear;
		_spotData._quadratic = quadratic;
	}

	void Spotlight::SetCutOffs(float cutOff, float outerCutOff)
	{
		_spotData._cutOff = glm::cos(glm::radians(cutOff));
		_spotData._outerCutOff = glm::cos(glm::radians(outerCutOff));
	}
}