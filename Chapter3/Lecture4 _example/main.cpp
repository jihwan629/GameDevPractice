#include "Game2D.h"
#include "Examples/PrimitivesGallery.h"
#include "RandomNumberGenerator.h"
#include "RigidCircle.h"
#include <vector>
#include <memory>

namespace jm
{
	using namespace std;

	static const auto gravity = vec2(0.0f, -9.8f);

	static const float l0 = 0.5f;
	static const float coeff_k = 100.0f;
	static const float coeff_d = 10.0f;

	static const float epsilon = 0.5f;
	static const float particle_radius = 0.04f;
	static const float particle_mass = 0.375f;

	class Particle
	{
	public:
		vec2 pos;
		vec2 vel;
		RGB  color;

		float rot;
		float angular_velocity;

		float age;
		float life;

		void init(const vec2 _pos, const vec2 _vel, const RGB  _color, 
			const float _age, const float _life,
			const float _rot, const float _angular_velocity )
		{
			pos = _pos;
			vel = _vel;
			color = _color;
			age = _age;
			life = _life;
			rot = _rot;
			angular_velocity = _angular_velocity;
		}

		void update(const float & dt)
		{
			const auto acc = gravity; //assumes GA only.

			vel += acc * dt;
			pos += vel * dt;

			rot += angular_velocity * dt;

			// update age.
			age += dt;

			// update color (blend with background color)
		}
	};

	class ParticleSystem
	{
	public:
		vector<Particle> particles;

		RandomNumberGenerator rn;

		vec2 init_pos;

		ParticleSystem()
		{
			reset();
		}

		auto getRandomUnitVector()
		{
			const float theta = rn.getFloat(0.0f, 3.141592f * 2.0f); // 0.0 ~ 2pi

			return vec2{cos(theta), -sin(theta)};
		}

		auto getRandomColor()
		{
			return RGB{ rn.getFloat(0.0f, 1.0f), rn.getFloat(0.0f, 1.0f), rn.getFloat(0.0f, 1.0f) };
		}

		void reset(vec2 mouse_pos = vec2(0.0f, 0.5f))
		{
			particles.clear();

			init_pos = mouse_pos;
			// initialize particles
			for (int i = 0; i < 100; ++i)
			{
				Particle new_particle;
				new_particle.init
				(
					init_pos + getRandomUnitVector() * rn.getFloat(0.001f, 0.03f),
					getRandomUnitVector() * rn.getFloat(0.01f, 2.0f),
					getRandomColor(),
					0.0f,
					rn.getFloat(0.3f, 0.8f),
					rn.getFloat(0.0f, 360.0f),
					rn.getFloat(-1.0f, 1.0f) * 360.0f * 4.0f
				);

				particles.push_back(new_particle);
			}
		}

		void update(const float & dt)
		{
			for (auto & pt : particles)
			{
				pt.update(dt);

				// remove particles when they are 1. too old, 2. out of screen.
				if (pt.age > pt.life) 
				{
					pt.init
					(
						init_pos + getRandomUnitVector() * rn.getFloat(0.001f, 0.03f),
						getRandomUnitVector() * rn.getFloat(0.01f, 2.0f),
						getRandomColor(),
						0.0f,
						rn.getFloat(0.3f, 0.8f),
						rn.getFloat(0.0f, 360.0f),
						rn.getFloat(-1.0f, 1.0f) * 360.0f * 4.0f
					);
				}
			}
		}

		void draw()
		{
			for (const auto & pt : particles)
			{
				if (pt.age > pt.life) continue;

				const float alpha = 1.0f - pt.age / pt.life;
				const RGB blended_color = { pt.color.r * alpha + 1.0f * (1.0f - alpha),
											pt.color.g * alpha + 1.0f * (1.0f - alpha),
											pt.color.b * alpha + 1.0f * (1.0f - alpha) };

				beginTransformation();
				translate(pt.pos);
				rotate(pt.rot);
				drawFilledStar(blended_color, particle_radius, particle_radius / 3.0f);
				endTransformation();
			}
		}
	};

	class Example : public Game2D
	{
	public:
		ParticleSystem ps;
		RigidCircle rb0, rb1;

		Example()
			: Game2D()
		{
			reset();
		}

		void reset(vec2 mouse_pos = vec2(0.0f, 0.5f))
		{
			ps.reset(mouse_pos);

			rb0.pos = vec2(0.0f, 0.5f);
			rb0.vel = vec2(0.0f, 0.0f);
			rb0.color = Colors::hotpink;
			rb0.radius = 0.08f;
			rb0.mass = 1.0f;

			rb1.pos = vec2(0.5f, 0.5f);
			rb1.vel = vec2(0.0f, 0.0f);
			rb1.color = Colors::yellow;
			rb1.radius = 0.08f;
			rb1.mass = rb0.mass * std::pow(rb1.radius / rb0.radius, 2.0f);
		}

		void update() override
		{
			const float dt = getTimeStep() * 0.4f;

			// update rb1 (Note: rb0 is fixed)
			{
				const auto distance = (rb1.pos - rb0.pos).getMagnitude();
				const auto direction = (rb1.pos - rb0.pos) / distance; // unit vector

				const auto spring_force = direction * -(distance - l0) * coeff_k +
					direction * -(rb1.vel - rb0.vel).getDotProduct(direction) * coeff_d;

				const auto accel = gravity + spring_force / rb1.mass;

				rb1.vel += accel * dt;
				rb1.pos += rb1.vel * dt;
			}

			// collision
			{
				for (auto &p : ps.particles)
				{
					const float distance = (p.pos - rb1.pos).getMagnitude();

					if (distance <= particle_radius + rb1.radius)
					{
						// compute impulse
						const auto vel_rel = p.vel - rb1.vel; // 상대 속도
						const auto normal = -(rb1.pos - p.pos) / (rb1.pos - p.pos).getMagnitude(); // 노말 벡터 n1

						// 현재 속도가 물체에 접근하는 방향인지 확인
						if (vel_rel.getDotProduct(normal) < 0.0f) // approaching
						{
							const auto impulse = normal * -(1.0f + epsilon) * vel_rel.getDotProduct(normal) /
								((1.0f / particle_mass) + (1.0f / rb1.mass));

							// update velocities of two bodies
							p.vel += impulse / particle_mass;
							//rb1.vel -= impulse / rb1.mass;
						}
					}
				}
			}
			
			ps.update(dt);

			drawLine(Colors::red, rb0.pos, Colors::red, rb1.pos);
			rb0.draw();

			ps.draw();

			rb1.draw();

			// reset button
			if (isKeyPressedAndReleased(GLFW_KEY_R)) reset();
			if (this->isMouseButtonPressedAndReleased(GLFW_MOUSE_BUTTON_1)) reset(getCursorPos());
		}

	};
}

int main(void)
{
	jm::Example().run();

	return 0;
}
