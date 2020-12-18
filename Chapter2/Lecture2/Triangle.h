#pragma once

#include "GeometricObject.h"

namespace jm
{
	class Triangle : public GeometricObject
	{
	public:
		float size;

		void init(const RGB &_color, const vec2 &_pos, const float &_size, const float &_angle = 0.0f)
		{
			GeometricObject::init(_color, _pos);
			size = _size;
			angle = _angle;
		}

		void drawGeometry() const override
		{
			drawFilledTriangle(color, size);
		}
	};
}
