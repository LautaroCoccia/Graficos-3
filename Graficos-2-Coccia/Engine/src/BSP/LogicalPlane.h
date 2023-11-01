#ifndef LOGICALPLANE_H
#define LOGICALPLANE_H
#include <iostream>
#include "../Export/Export.h"
#include "../glm/glm/vec3.hpp"
#include "../Entity/Entity.h"	
using namespace std;
using namespace glm;
//#include "cube/Cube.h"
namespace Engine
{

	class EXPORT_API LogicalPlane : public Entity
	{
	public:
		LogicalPlane();
		LogicalPlane(std::string name, const char* path, vec3 inNormal);
		~LogicalPlane();
		float GetDistanceToPoint(vec3 point);
		bool FrontPlane(vec3 point);
	private:
		vec3 normal;
		float distance;
	};
}
#endif