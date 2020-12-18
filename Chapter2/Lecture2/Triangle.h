#pragma once

#include "GeometricObject.h"

namespace jm
{
	class Triangle : public GeometricObject
	{
	public:
		void draw()
		{
			beginTransformation();
			{
				translate(pos);
				drawFilledTriangle(color, size);
			}
			endTransformation();
		}
	};
}
