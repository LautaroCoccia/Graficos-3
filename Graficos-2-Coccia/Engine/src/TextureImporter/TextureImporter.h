#ifndef TEXTURE_IMPORTER_H
#define TEXTURE_IMPORTER_H

#include "..\Export\Export.h"
#include "..\Renderer\Renderer.h"
#include <string>
namespace Engine
{
	struct TextureData
	{
		unsigned char* _data;
		int _width;
		int _height;
		int _nrChannels;
		unsigned int _diffuse;
	};
	class EXPORT_API TextureImporter
	{
		
		int _width, _height, _nrChannels;
		
		unsigned char* _data;

	public:
		
		TextureImporter();
		~TextureImporter();

		void ImportTexture(Renderer* renderer, const char* name, unsigned int& texture);
		void ImportTexture(Renderer* renderer, const char* filePath, TextureData& _textureData);
		unsigned int TextureFromFile(const char* path, std::string const& directory, bool gamma = false);

		//void ImportTextures(Renderer* renderer, const char* filePath, TextureData& _textureData);
	};
}

#endif