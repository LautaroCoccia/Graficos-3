#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "../Transform/Transform.h"
#include "../Renderer/Renderer.h"
using namespace glm;
namespace Engine
{
	enum class ENTITY_COLOR
	{
		WHITE, BLACK, GRAY,
		RED, GREEN, BLUE
	};

	

	class EXPORT_API Entity : public Transform
	{
		
	protected:
		
		bool _isTrigger;
		bool _isStatic;
		Renderer* _renderer;

	public:
		Entity();
		~Entity();

		void SetTriggerState(bool state);
		void SetStaticState(bool state);

		bool GetTriggerState();
		bool GetStaticState();

		GeneralMatrix GetGeneralMatrix();
		Transforms GetTransform();
		virtual void TriggerCollision(Entity* other) = 0;
	};
}
#endif