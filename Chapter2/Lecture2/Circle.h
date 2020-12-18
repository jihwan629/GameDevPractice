#pragma once

#include "GeometricObject.h"

namespace jm
{
	class Circle : public GeometricObject
	{
	public:
		void draw()
		{
			beginTransformation();
			{
				translate(pos);
				drawFilledCircle(color, size);
			}
			endTransformation();
		}
	};
}
