#ifndef LOGICALPLANE_H
#define LOGICALPLANE_H
#include <iostream>
#include "../Export/Export.h"
#include "../Cube/Cube.h"
using namespace std;
using namespace glm;
//#include "cube/Cube.h"
namespace Engine
{

	class EXPORT_API LogicalPlane : public Cube
	{
	public:
		LogicalPlane();
		LogicalPlane(std::string name, const char* path, vec3 inNormal);
		~LogicalPlane();
		float GetDistanceToPoint(vec3 point);
		bool GetSide(vec3 point);
		//void TriggerCollision(Entity* other) override;
	private:
		vec3 normal;
		float distance;
	};
}
#endif