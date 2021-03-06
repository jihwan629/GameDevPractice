#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"
#include "RigidCircle.h"
#include <vector>
#include <memory>

// 행 열
const int row = 5, col = 5;

// 힘 구하는 방향
// 형제 : 왼쪽, 오른쪽. 부모 : 왼쪽 위, 위, 오른쪽 위.
int dir_row[] { 0, 0, -1, -1, -1 };
int dir_col[] {-1, 1, -1, 0, 1 };

// 스프링 그리는 방향
// 오른쪽, 오른쪽 아래, 아래, 왼쪽 아래
int draw_row[]{ 0, 1, 1, 1 };
int draw_col[]{ 1, 1, 0, -1 };

namespace jm
{
	class Example : public Game2D
	{
	public:
		std::vector<std::shared_ptr<RigidCircle>> circles;

		Example()
			: Game2D()
		{
			reset();
		}

		void reset()
		{
			circles.clear();

			// Initial circles
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					auto temp = std::make_shared<RigidCircle>();
					temp->init
						(
							vec2(-0.5f + j * 1.0f / (col - 1), 0.75f - i * 1.0f / (row - 1)), 
							vec2(0.0f, 0.0f),
							(fixedCircle(i, j)) ? Colors::yellow : Colors::blue,
							0.03f, 
							1.0f
						);

					circles.push_back(std::move(temp));
				}
			}
		}

		void drawWall()
		{
			setLineWidth(5.0f);
			drawLine(Colors::blue, { -1.0f, -1.0f }, Colors::blue, { 1.0f, -1.0f });
			drawLine(Colors::blue, { 1.0f, -1.0f }, Colors::blue, { 1.0f, 1.0f });
			drawLine(Colors::blue, { -1.0f, -1.0f }, Colors::blue, { -1.0f, 1.0f });
		}

		// 스프링 그리기
		void drawSpring()
		{
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					for (int d = 0; d < sizeof(draw_row) / sizeof(int); d++)
					{
						int _i = i + draw_row[d], _j = j + draw_col[d];
						if (inCircles(_i, _j))
							drawLine
								(
									Colors::red, circles[i * col + j]->pos, 
									Colors::red, circles[_i * col + _j]->pos
								);
					}
				}
			}
		}

		// 고정 점인지 구분
		bool fixedCircle(int i, int j)
		{
			return (i == 0 && (j == 0 || j == col - 1)) ? true : false;
		}

		// 형제, 부모 탐색시 범위를 벗어난지 구분
		bool inCircles(int i, int j)
		{
			return (i >= 0 && j >= 0 && i < row && j < col) ? true : false;
		}

		void update() override
		{
			const float dt = getTimeStep() * 0.4f;
			const float epsilon = 0.5f;

			// coefficients
			const vec2 gravity(0.0f, -9.8f);
			const float l0 = 0.3f;
			const float coeff_k = 200.0f;
			const float coeff_d = 5.0f;

			// update circles
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					if (fixedCircle(i, j)) continue;

					auto &rb1 = circles[i * col + j];

					vec2 total_spring_force(0.0f, 0.0f);

					for (int d = 0; d < sizeof(dir_row) / sizeof(int); d++)
					{
						int _i = i + dir_row[d], _j = j + dir_col[d];

						if (!inCircles(_i, _j)) continue;

						auto &rb0 = circles[_i * col + _j];

						const auto distance = (rb1->pos - rb0->pos).getMagnitude();
						const auto direction = (rb1->pos - rb0->pos) / distance; // unit vector

						const auto spring_force = direction * -(distance - l0) * coeff_k +
							direction * -(rb1->vel - rb0->vel).getDotProduct(direction) * coeff_d;

						total_spring_force += spring_force;

						if (!fixedCircle(_i, _j))
							rb0->vel -= spring_force / rb0->mass * dt; // reaction
					}

					const auto accel = gravity + total_spring_force / rb1->mass;
					rb1->vel += accel * dt;
				}
			}
			
			// update position
			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < col; j++)
				{
					if (!fixedCircle(i, j))
						circles[i * col + j]->pos += circles[i * col + j]->vel * dt;
				}
			}

			// draw
			drawWall();
			drawSpring();
			for (auto &circle : circles) circle->draw();

			// reset button
			if (isKeyPressedAndReleased(GLFW_KEY_R)) reset();
		}

	};
}

int main(void)
{
	jm::Example().run();

	return 0;
}
