#pragma once

#include "GeometricObject.h"

namespace jm
{
	class Box : public GeometricObject
	{
	public:
		float width;
		float height;

		void init(const RGB &_color, const vec2 &_pos, const float &_width, const float &_height, const float &_angle = 0.0f)
		{
			GeometricObject::init(_color, _pos);
			width = _width;
			height = _height;
			angle = _angle;
		}

		void drawGeometry() const override
		{
			drawFilledBox(color, this->width, this->height);
		}
	};
}