#ifndef TIME_H
#define TIME_H

#include "../src/Export/Export.h"

namespace Engine
{
	class EXPORT_API Time
	{
	public:
		static void DeltaTime(float& time);	
	};
}

#endif // !TIME_H

