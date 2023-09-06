#ifndef SHADER_H
#define SHADER_H

#include <string>
#include "..\Export\Export.h"

namespace Engine
{
	class EXPORT_API Shader
	{
	private:
		unsigned int _shader;

		unsigned int CompileShader(unsigned int type, const char* source);
		unsigned int CreateShader(const char* vertexShader, const char* fragmentShader);
	
	public:
		Shader();
		~Shader();

		void SetShader(const char* vertexShader, const char* fragmentShader);
		void ClearShader();

		unsigned int GetShader();
	};
}

#endif