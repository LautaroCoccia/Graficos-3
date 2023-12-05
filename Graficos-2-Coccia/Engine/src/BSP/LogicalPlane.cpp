#include "LogicalPlane.h"

namespace Engine
{
    LogicalPlane::LogicalPlane() : Cube("non",NULL)
    {

        normal = vec3(0,0,0);
        distance = 1;
    }
    LogicalPlane::LogicalPlane(string name, const char* path, vec3 inNormal) : Cube(name, path)//completar
    {
        normal = inNormal;
        distance = -dot(normal, GetPosition());
    }

    LogicalPlane::~LogicalPlane()
    {
    }

    float LogicalPlane::GetDistanceToPoint(vec3 point)
    {
        // distancia positiva si el punto esta frente al plano
        // distancia negativa si el punto esta espaldas al plano

        vec3 aux;
        aux.x = normal.x * 2;
        aux.y = normal.y * 2;
        aux.z = normal.z * 2;

        return  (dot(point - GetPosition(), normal) + distance) / (aux.x + aux.y + aux.z);

    }

    bool LogicalPlane::GetSide(glm::vec3 point)
    {
        if (GetDistanceToPoint(point) > 0.0f)
            return true;
        return false;
    }
    /*void LogicalPlane::TriggerCollision(Entity* other)
    {
        if (!other->GetStaticState())
        {
            glm::vec3 newPos = _transform.position;
            ReturnToPrevPosition();
            newPos -= _transform.position;

            other->SetPosition(other->_transform.position + newPos);
        }
        else
        {
            ReturnToPrevPosition();
        }
    }*/

}
