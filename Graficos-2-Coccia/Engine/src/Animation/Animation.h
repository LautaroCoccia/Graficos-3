#ifndef ANIMATION_H
#define ANIMATION_H

#include "..\Export\Export.h"
#include "glm/glm/glm.hpp"
#include <vector>

using namespace glm;
namespace Engine
{
	struct Frame
	{
		vec4 _uv;
		//int _framesCount;
	};

	class Sprite;
	
	class EXPORT_API Animation
	{
	private:
		vec4 uvs = vec4(0, 0, 0, 0);
		Sprite* _sprite;

		ivec2 _dimensions;
		std::vector<Frame> _frames;

		int _currentFrame;
		int _maxFrames;

		int _firstIndex;
		int _lastIndex;

		float _length;
		float _time;
	
		void ChangeFrame();
	public:
		Animation();
		~Animation();

		void InitSpriteSheet(Sprite* spriteSheet, const glm::ivec2& tileDimensions);
		void AddFrame(float durationInSec, int firstIndex, int lastIndex);
		void UpdateFrame(float deltaTime);
		vec4 GetUVs(int index);
		vec4 GetUVsFromVector(int index);
		int GetCurrentFrame();
	};
}
#endif