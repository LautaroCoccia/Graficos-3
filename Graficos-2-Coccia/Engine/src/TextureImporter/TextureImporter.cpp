#include "TextureImporter.h"

#include "GL\glew.h"
#include "glm\glm.hpp"

#include "..\TextureImporter\stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>

using namespace std;

namespace Engine
{
	TextureImporter::TextureImporter()
	{
	
	}
	
	TextureImporter::~TextureImporter()
	{
	
	}

	void TextureImporter::ImportTexture(Renderer* renderer, const char* name, unsigned int& texture)
	{
		stbi_set_flip_vertically_on_load(true);

		_data = stbi_load(name, &_width, &_height, &_nrChannels, 0);

		if (!_data)
		{
			cout << "failed to load texture" << endl;
			return;
		}

		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		if (_nrChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, _data);
		}

		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(_data);

		glUseProgram(renderer->GetShader());
		//glUniform1i(glGetUniformLocation(renderer->GetShader(), "ourTexture"), 0);
	}
	void TextureImporter::ImportTexture(Renderer* renderer, const char* filePath, TextureData& textureData)
	{
	
		stbi_set_flip_vertically_on_load(true);
	
		textureData._data = stbi_load(filePath, &textureData._width, &textureData._height, &textureData._nrChannels, 0);
	
		if (!textureData._data)
		{
			cout << "failed to load texture" << endl;
	
		}
		glGenTextures(1, &textureData._diffuse);
		glBindTexture(GL_TEXTURE_2D, textureData._diffuse);
		// set the texture wrapping parameters 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method) 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
		if (textureData._nrChannels == 4)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureData._width, textureData._height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData._data);
		}
		else
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureData._width, textureData._height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureData._data);
		}
	
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE0);
		//ImportTexture(renderer, filePath, textureData._specular);
		stbi_image_free(textureData._data);
	
		//glUseProgram(renderer->GetShader());
		//glUniform1i(glGetUniformLocation(renderer->GetShader(), "ourTexture"), 0);
		//texture = _textureData._texture;
		//return _textureData;
	}

	unsigned int TextureImporter::TextureFromFile(const char* path, std::string const& directory, bool gamma)
	{
		string filename = string(path);
		filename = directory + '/' + path;
		
		unsigned int textureID;
		glGenTextures(1, &textureID);
		
		int width, height, nrComponents;
		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
		if (data)
		{
			GLenum format;
			if (nrComponents == 1)
				format = GL_RED;
			else if (nrComponents == 3)
				format = GL_RGB;
			else if (nrComponents == 4)
				format = GL_RGBA;
		
			glBindTexture(GL_TEXTURE_2D, textureID);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Texture failed to load at path: " << path << std::endl;
			stbi_image_free(data);
		}
		
		return textureID;
	}
	//void TextureImporter::ImportTextures(Renderer* renderer, const char* diffuse, const char* specular, TextureData& _textureData)
	//{
	//	ImportTexture(renderer, diffuse, _textureData);
	//	void ImportTexture(Renderer * renderer, const char* name, unsigned int& texture);
	//
	//}
}