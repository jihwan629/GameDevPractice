#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"
#include <vector>
#include <memory>

#include "GeometricObject.h"

namespace jm
{
	class Example : public Game2D
	{
	public:
		//std::vector<GeometricObject *> my_objs;
		std::vector<std::unique_ptr<GeometricObject>> my_objs;

		Example()
			: Game2D()
		{
			//my_objs.push_back(GeometricObject::makeTriangle(Colors::gold, vec2{ -0.5f, 0.2f }, 0.25f));
			//my_objs.push_back(GeometricObject::makeCircle(Colors::olive, vec2{ 0.1f, 0.1f }, 0.2f));
			//my_objs.push_back(GeometricObject::makeBox(Colors::blue, vec2{ 0.0f, 0.5f }, 0.15f, 0.25f));
			//my_objs.push_back(GeometricObject::makeStar(Colors::gold, vec2{ 0.0f, -0.5f }, 0.25f, 0.15f));

			my_objs.push_back(std::unique_ptr<GeometricObject>
				(GeometricObject::makeTriangle(Colors::gold, vec2{ -0.5f, 0.2f }, 0.25f)));
			my_objs.push_back(std::unique_ptr<GeometricObject>
				(GeometricObject::makeCircle(Colors::olive, vec2{ 0.1f, 0.1f }, 0.2f)));
			my_objs.push_back(std::unique_ptr<GeometricObject>
				(GeometricObject::makeBox(Colors::blue, vec2{ 0.0f, 0.5f }, 0.15f, 0.25f)));
		}

		~Example()
		{
			//delete is unnecessary with shared_ptr
			//for (const auto & obj : my_objs)
			//	delete obj;
		}

		void update() override
		{
			for (const auto & obj : my_objs)
				obj->draw();
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
