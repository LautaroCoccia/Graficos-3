#include "Time.h"
#include <time.h>
#include <iostream>

namespace Engine
{
	double oldTime = clock();
	
	void Time::DeltaTime(float& time)
	{
		double actualTime = clock();
		float deltaTime = (float)((actualTime - oldTime) / 1000.0f);
		oldTime = actualTime;
		time = deltaTime;
	}
}
