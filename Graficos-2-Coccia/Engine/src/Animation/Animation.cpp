#include "Animation.h"
#include <iostream>

using namespace std;

namespace Engine
{
	Animation::Animation()
	{
		_sprite = NULL;
		_dimensions.x = 0;
		_dimensions.y = 0;
		_currentFrame = 0;

		_firstIndex = 0;
		_lastIndex  = 0;
	}

	Animation::~Animation()
	{

	}

	void Animation::InitSpriteSheet(Sprite* spriteSheet, const  glm::ivec2& tileDimensions)
	{
		_sprite = spriteSheet;
		_dimensions = tileDimensions;
		//Dimensions son la cantidad de indices en X e Y que tiene nuesta textura
	}	
	
	void Animation::AddFrame(float durationInSec, int firstIndex, int lastIndex)
	{
		_firstIndex = firstIndex;
		_lastIndex = lastIndex;
		_currentFrame = 0;

		for (int i = firstIndex; i <= lastIndex; i++)
		{
			Frame frame;
			int xTile = i % _dimensions.x; //Esto impide que xTile sea mayor a la dimension en x
			int yTile = i / _dimensions.x; //Esto dice que tiene que cortar en horizontal si pones Y la secuencia se corta en un indice anterior 
			frame._uv.x = xTile / (float)_dimensions.x; //posicion en x
			frame._uv.y = yTile / (float)_dimensions.y; //posicion en y
			frame._uv.z = 1.0f / (float)_dimensions.x;  //ancho
			frame._uv.w = 1.0f / (float)_dimensions.y;  //alto

			_frames.push_back(frame);
		}
		_length = durationInSec / _frames.size(); //El tiempo total se divide entre la cantidad de frames
	}

	void Animation::UpdateFrame(float deltaTime)
	{
		float t = 0;
		t = deltaTime;
		_time += t;

		if (_time >= _length)
		{
			_currentFrame++;
			if (_currentFrame >= _frames.size())
				_currentFrame = 0;

			ChangeFrame();
			_time = t;
		}
	}

	void Animation::ChangeFrame()
	{
		uvs = GetUVsFromVector(_currentFrame);
	}

	vec4 Animation::GetUVs(int index)
	{
		int xTile = index % _dimensions.x; //Esto impide que xTile sea mayor a la dimension en x
		int yTile = index / _dimensions.x;
		
		uvs.x = xTile / (float)_dimensions.x; //posicion en x
		uvs.y = yTile / (float)_dimensions.y; //posicion en y
		uvs.z = 1.0f / (float)_dimensions.x;  //ancho
		uvs.w = 1.0f / (float)_dimensions.y;  //alto

		return uvs;
		
	}
	vec4 Animation::GetUVsFromVector(int index)
	{
		return _frames[index]._uv;
	}

	int Animation::GetCurrentFrame()
	{	
		return _currentFrame;
	}
}