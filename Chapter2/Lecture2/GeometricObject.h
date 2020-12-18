#pragma once

#include "Game2D.h"

namespace jm
{
	class GeometricObject
	{
	public:
		vec2 pos;
		RGB color;
		float angle;

		void init(const RGB &_color, const vec2 &_pos, const float &_angle = 0.0f) 
		{
			color = _color;
			pos = _pos;
			angle = _angle;
		}

		// 순수 가상 함수
		virtual void drawGeometry() const = 0;

		void draw()
		{
			beginTransformation();
			{
				translate(pos);
				rotate(angle);
				drawGeometry();
			}
			endTransformation();
		}
	};
}
