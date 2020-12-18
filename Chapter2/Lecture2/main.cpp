#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"
#include "Triangle.h"
#include "Circle.h"

namespace jm
{
	class Example : public Game2D
	{
	public:
		Triangle my_tri;
		Circle my_cir;

		Example()
			: Game2D()
		{
			my_tri.init(Colors::gold, vec2{ -0.5f, 0.2f }, 0.25f);
			my_cir.init(Colors::olive, vec2{ 0.1f, 0.1f }, 0.2f);
		}

		void update() override
		{
			my_tri.draw();
			my_cir.draw();

			// blue box
			//beginTransformation();
			//{
			//	translate(vec2{ 0.5f, 0.0f });
			//	drawFilledBox(Colors::blue, 0.25f, 0.3f);
			//}
			//endTransformation();
		}
	};
}

int main(void)
{
	jm::Example().run();
	//jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
	//jm::PrimitivesGallery().run();

	return 0;
}
