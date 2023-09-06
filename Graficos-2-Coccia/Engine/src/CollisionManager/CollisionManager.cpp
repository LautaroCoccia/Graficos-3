#include "CollisionManager.h"
#include <iostream>
#include <algorithm>

namespace Engine
{
	CollisionManager::CollisionManager() 
	{
		
	}
	
	CollisionManager::~CollisionManager() 
	{
		if(!_vec.empty())
			_vec.clear();
	}
	
	void CollisionManager::AddNewObject(Entity* obj)
	{
		_vec.push_back(obj);
	}

	void CollisionManager::RemoveObject(Entity* obj)
	{
		std::remove(_vec.begin(), _vec.end(), obj);
	}
	
	bool CollisionManager::CheckCollision(Entity* one, Entity* two)
	{
		bool collisionX = one->_transform.position.x + one->_transform.scale.x >= two->_transform.position.x &&
			two->_transform.position.x + two->_transform.scale.x >= one->_transform.position.x;
	
		bool collisionY = one->_transform.position.y + one->_transform.scale.y >= two->_transform.position.y &&
			two->_transform.position.y + two->_transform.scale.y >= one->_transform.position.y;

		return collisionX && collisionY;
	}

	void CollisionManager::CheckAllCollisions()
	{
		if (!_vec.empty() && _vec.size() > 1)
		{
			for (int i = 0; i < _vec.size(); i++)
			{
				for (int j = 0; j < _vec.size(); j++)
				{
					if (CheckCollision(_vec[i], _vec[j]) && i != j)
					{
						_vec[i]->TriggerCollision(_vec[j]);
					}
				}
			}
		}
		else
		{
			std::cout << "The Vector is EMPTY! Add more entities" << std::endl;
		}
	}
}