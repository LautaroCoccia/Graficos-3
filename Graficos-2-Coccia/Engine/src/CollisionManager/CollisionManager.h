#ifndef COLLISIONMANAGER_H
#define COLLISIONMANAGER_H

#include <vector>
#include "..\Export\Export.h"
#include "..\Entity\Entity.h"

namespace Engine
{
	class EXPORT_API CollisionManager
	{
		std::vector<Entity*> _vec;

	public:
		CollisionManager();
		~CollisionManager();

		void AddNewObject(Entity* obj);
		void RemoveObject(Entity* obj);

		bool CheckCollision(Entity* one, Entity* two);
		void CheckAllCollisions();
	};
}
#endif