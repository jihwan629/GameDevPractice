#pragma once

#include "Game2D.h"

namespace jm
{
	class GeometricObject
	{
	public:
		vec2 pos;
		RGB color;
		float size;

		void init(const RGB &_color, const vec2 &_pos, const float &_size)
		{
			color = _color;
			pos = _pos;
			size = _size;
		}
	};
}
