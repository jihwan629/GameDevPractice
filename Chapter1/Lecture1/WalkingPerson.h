#pragma once

#include "Game2D.h"

namespace jm
{
	/*
	TODO:
	- add left arm and left leg
	- make a Person class and use it to draw many people.
	- make an Ironman and allow for him to shoot repulsor beam with his right hand
	*/

	class WalkingPerson : public Game2D
	{
		float time = 0.0f;

		bool isJump = false;
		float height = 0.0f;
		const float maxHeight = 1.0f;

		bool isAttack = false;
		float startAttackTime = 0.0f;
		const float attackTime = 0.5f;

	public:
		void update() override
		{
			// jump when press spacebar
			if (isKeyPressedAndReleased(GLFW_KEY_SPACE) && !isJump) isJump = true;
			if (isKeyPressedAndReleased(GLFW_KEY_Z) && !isAttack)
			{
				isAttack = true;
				startAttackTime = time;
			}

			// change height
			{
				height += (isJump) ? 0.1f : -0.1f;

				if (height > maxHeight)
				{
					isJump = false;
					height = maxHeight;
				}
				else if (height < 0) height = 0;

				translate(0.0f, height);
			}

			// Laser
			{
				if (isAttack && (time - startAttackTime) > attackTime) isAttack = false;

				if (isAttack)
				{
					beginTransformation();
					translate(1.0f, 0.0f);
					drawFilledBox(Colors::skyblue, 1.2f, 0.1f);
					endTransformation();
				}
			}

			// silver arm
			beginTransformation();

			{
				if (isAttack) rotate(90.0f);
				else rotate(sin(time * 5.0f) * 30.0f * -1.0f);
			}

			scale(1.0f, 2.0f);
			translate(0.0f, -0.1f);
			drawFilledBox(Colors::silver, 0.05f, 0.18f);
			endTransformation();

			// olive leg
			beginTransformation();
			translate(0.0f, -0.6f);
			translate(0.0f, 0.2f);
			rotate(sinf(time * 5.0f + 3.141592f) * 30.0f * -1.0f);	// animation!
			translate(0.0f, -0.2f);
			drawFilledBox(Colors::olive, 0.1f, 0.4f);
			endTransformation();

			// gold face
			beginTransformation();
			translate(0.0f, 0.12f);
			drawFilledCircle(Colors::gold, 0.08f);
			translate(0.05f, 0.03f);
			drawFilledCircle(Colors::white, 0.01f); // while eye

			endTransformation();

			// red body
			beginTransformation();
			scale(1.0f, 2.0f);
			translate(0.0f, -0.1f);
			drawFilledBox(Colors::red, 0.13f, 0.2f);
			endTransformation();

			// yellow arm
			beginTransformation();
			rotate(sin(time*5.0f) * 30.0f);					// animation!
			scale(1.0f, 2.0f);
			translate(0.0f, -0.1f);
			drawFilledBox(Colors::yellow, 0.05f, 0.18f);
			endTransformation();

			// green leg
			beginTransformation();
			translate(0.0f, -0.6f);
			translate(0.0f, 0.2f);
			rotate(sinf(time*5.0f + 3.141592f) * 30.0f);	// animation!
			translate(0.0f, -0.2f);
			drawFilledBox(Colors::green, 0.1f, 0.4f);
			endTransformation();

			time += this->getTimeStep();
		}
	};
}