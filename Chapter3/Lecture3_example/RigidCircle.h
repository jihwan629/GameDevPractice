#pragma once

#include "Game2D.h"

namespace jm
{
	class RigidCircle
	{
	public:
		vec2 pos;
		vec2 vel;
		RGB color = Colors::hotpink;
		float radius = 0.1f;
		float mass = 1.0f;

	public:
		void init(const vec2 &_pos, const vec2 &_vel, const RGB &_color
			, const float &_radius, const float &_mass)
		{
			pos = _pos;
			vel = _vel;
			color = _color;
			radius = _radius;
			mass = _mass;
		}

		// ±Ì¿∫ ∫πªÁ
		void init(RigidCircle _circle)
		{
			pos = _circle.pos;
			vel = _circle.vel;
			color = _circle.color;
			radius = _circle.radius;
			mass = _circle.mass;
		}


		void draw()
		{
			beginTransformation();
			{
				translate(pos);
				drawFilledCircle(color, radius - 1e-3f);
				setLineWidth(2.0f);
				drawWiredCircle(Colors::black, radius);
			}
			endTransformation();
		}

		void update(const float & dt)
		{
			static const vec2 gravity = vec2(0.0f, -9.8f);
			static const float coef_res = 0.7f; // coefficient of restitution
			static const float coef_friction = 0.99f; // friction (not physical)

			// numerical integration
			vel += gravity * dt;
			pos += vel * dt;

			// wall collision, friction
			if (1.0f - pos.x <= radius) // right wall
			{
				pos.x = 1.0f - radius;

				if (vel.x >= 0.0f)
					vel.x *= -1.0f * coef_res;
			}

			if (pos.x <= -1.0f + radius) // left wall
			{
				pos.x = -1.0f + radius;

				if (vel.x <= 0.0f)
					vel.x *= -1.0f * coef_res;
			}

			if (pos.y <= -1.0f + radius) // ground
			{
				pos.y = -1.0f + radius;

				if (vel.y <= 0.0f)
					vel.y *= -1.0f * coef_res;

				vel.x *= coef_friction;
			}
		}
	};
}
