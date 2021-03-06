#include "Game2D.h"
#include "PrimitivesGallery.h"
#include "TankExample.h"
#include "FaceExample.h"
#include "WalkingPerson.h"
#include "SolarSystem.h"

namespace jm
{
	class RotatingStarExample : public Game2D
	{
		float time = 0.0f;

	public:
		void update() override
		{
			rotate(time * 180.0f);
			drawFilledStar(Colors::gold, 0.4f, 0.25f);

			time += this->getTimeStep();
		}
	};

	class TransformationsExample : public Game2D
	{
	public:
		float time = 0;

		void update() override
		{
			//{
			//	// 4. 삼각형 움직이기

			//	const float dx = 0.0f;
			//	const float dy = 0.0f;

			//	// 5. 좌표계 바꾸기

			//	beginTransformation();

			//	translate(0.1f, 0.0f);

			//	// 1. 점 그리기

			//	//const vec2 point = vec2(0.0f, 0.0f);
			//	//drawPoint(Colors::black, point, 5.0f);

			//	// 2. 선 그리기

			//	const vec2 p0(0.0f + dx, 0.0f + dy);
			//	const vec2 p1(0.5f + dx, 0.5f + dy);

			//	drawLine(Colors::red, p0, Colors::blue, p1);

			//	// 3. 삼각형 그리기

			//	const vec2 p2(0.5f + dx, 0.0f + dy);

			//	drawLine(Colors::red, p1, Colors::blue, p2);
			//	drawLine(Colors::red, p2, Colors::blue, p0);

			//	endTransformation();

			//	// 6. 삼각형 추가

			//	translate(-0.1f, 0.0f);
			//	drawLine(Colors::red, p0, Colors::blue, p1);
			//	drawLine(Colors::red, p1, Colors::blue, p2);
			//	drawLine(Colors::red, p2, Colors::blue, p0);

			//	// 7. 좌표계 초기화
			//}
			
			//{
			//	// 8. 박스 그리기

			//	setLineWidth(3.0f);

			//	drawWiredBox(Colors::gold, 0.5f, 0.25f);

			//	// 9. 박스 회전

			//	beginTransformation();

			//	rotate(30.0f);
			//	drawWiredBox(Colors::skyblue, 0.5f, 0.25f);

			//	endTransformation();

			//	// 10. translate + 회전

			//	beginTransformation();

			//	// 컴퓨터 그래픽스는 역순으로 이루어 진다 ( 회전 > translate )
			//	translate(0.25f, 0.0f);
			//	rotate(30.0f);
			//	drawWiredBox(Colors::red, 0.5f, 0.25f);

			//	endTransformation();

			//	// 10.  회전 +translate

			//	beginTransformation();

			//	rotate(30.0f);
			//	translate(0.25f, 0.0f);
			//	drawWiredBox(Colors::blue, 0.5f, 0.25f);

			//	endTransformation();
			//}

			/*{
				setLineWidth(3.0f);

				const vec2 center_of_rot(-0.4f, 0.0f);

				translate(center_of_rot);
				rotate(45.0f);
				translate(-center_of_rot);

				drawWiredBox(Colors::gold, 0.5f, 0.25f);
				drawPoint(Colors::black, center_of_rot, 5.0f);
			}*/

			{
				setLineWidth(3.0f);

				rotate(time * 90.0f);
				translate(0.5f, 0.0f);
				scale(2.0f, 0.25f);
				drawWiredBox(Colors::gold, 0.5f, 0.5f);

				time += this->getTimeStep();
			}
		}
	};

	class MouseExample :public Game2D
	{
	public:
		void update() override
		{
			const vec2 mouse_pos = getCursorPos();

			//std::cout << mouse_pos << std::endl;

			if (this->isMouseButtonPressed(GLFW_MOUSE_BUTTON_1) == true)
			{
				translate(mouse_pos);
				drawFilledCircle(Colors::gold, 0.1f);
			}else if (this->isMouseButtonPressed(GLFW_MOUSE_BUTTON_2) == true)
			{
				translate(mouse_pos);
				drawFilledCircle(Colors::red, 0.1f);
			}
		}
	};
}

int main(void)
{
	// 1.1
	//jm::Game2D().init("This is my digital canvas!", 1280, 960, false).run();
	//jm::RotatingStarExample().init("RotatingStarExample", 1280, 960, false, 2).run();

	// 1.2
	//jm::TransformationsExample().run();
	//jm::PrimitivesGallery().init("Primitive Gallery", 1280, 960, false).run();
	//jm::SolarSystem().run();
	//jm::FaceExample().run();

	// 1.3
	//jm::TankExample().run();
	//jm::MyTankExample().run();
	//jm::WalkingPerson().run();

	// 1.4
	jm::MouseExample().init("This is my digital canvas!", 1000, 1000, false).run();

	return 0;
}
