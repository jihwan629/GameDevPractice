#pragma once

#include "Game2D.h"
#include <map>
#include <fstream>

namespace jm
{
	class Actor
	{
	public:
		virtual void moveUp(float dt) = 0;
		virtual void moveDown(float dt) = 0;
		virtual void moveRight(float dt) = 0;
		virtual void moveLeft(float dt) = 0;
		virtual void shoot(float dt) = 0;
	};

	class Command
	{
	public:
		virtual ~Command() {}
		virtual void execute(Actor& actor, float dt) = 0;
	};

	class UpCommand : public Command 
	{
	public:
		virtual void execute(Actor& actor, float dt) override
		{
			actor.moveUp(dt);
		}
	};

	class DownCommand : public Command
	{
	public:
		virtual void execute(Actor &actor, float dt) override
		{
			actor.moveDown(dt);
		}
	};

	class RightCommand : public Command
	{
	public:
		virtual void execute(Actor &actor, float dt) override
		{
			actor.moveRight(dt);
		}
	};

	class LeftCommand : public Command
	{
	public:
		virtual void execute(Actor &actor, float dt) override
		{
			actor.moveLeft(dt);
		}
	};

	class ShootCommand : public Command
	{
	public:
		virtual void execute(Actor &actor, float dt) override
		{
			actor.shoot(dt);
		}
	};

	class MyBullet
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		vec2 velocity = vec2(0.0f, 0.0f);

		void draw()
		{
			beginTransformation();
			translate(center);
			drawFilledRegularConvexPolygon(Colors::yellow, 0.02f, 8);
			drawWiredRegularConvexPolygon(Colors::gray, 0.02f, 8);
			endTransformation();
		}

		void update(const float &dt)
		{
			center += velocity * dt;
		}

		MyBullet()
		{
			std::cout << "bullet construct!" << std::endl;
		}

		~MyBullet()
		{
			std::cout << "bullet delete!" << std::endl;
		}
	};

	class MyTank : public Actor
	{
	public:
		vec2 center = vec2(0.0f, 0.0f);
		//vec2 direction = vec2(1.0f, 0.0f, 0.0f);
		std::vector<std::unique_ptr<MyBullet>> bullets;

		~MyTank()
		{
			bullets.clear();
		}

		void moveUp(float dt) override
		{
			center.y += 0.5f * dt;
		}

		virtual void moveDown(float dt) override
		{
			center.y -= 0.5f * dt;
		}

		virtual void moveRight(float dt) override
		{
			center.x += 0.5f * dt;
		}

		virtual void moveLeft(float dt) override
		{
			center.x -= 0.5f * dt;
		}

		virtual void shoot(float dt) override
		{
			if (bullets.size() < 5)
			{
				auto bullet = std::make_unique<MyBullet>();
				bullet->center = center;
				bullet->center.x += 0.2f;
				bullet->center.y += 0.1f;
				bullet->velocity = vec2(2.0f, 0.0f);

				bullets.push_back(std::move(bullet));
			}
		}

		void draw()
		{
			beginTransformation();
			{
				translate(center);
				drawFilledBox(Colors::green, 0.25f, 0.1f); // body
				translate(-0.02f, 0.1f);
				drawFilledBox(Colors::blue, 0.15f, 0.09f); // turret
				translate(0.15f, 0.0f);
				drawFilledBox(Colors::red, 0.15f, 0.03f);  // barrel
			}
			endTransformation();
		}
	};

	class InputHandler
	{
	public:
		Command * button_up		= nullptr;
		Command * button_down	= nullptr;
		Command * button_right	= nullptr;
		Command * button_left	= nullptr;
		Command * button_shoot	= nullptr;

		std::map<int, Command *> key_pressed_command_map;
		std::map<int, Command *> key_pressedNreleased_command_map;

		InputHandler()
		{
			//button_up			= new UpCommand;
			//button_down		= new DownCommand;
			//button_right		= new RightCommand;
			//button_left		= new LeftCommand;
			//button_shoot		= new ShootCommand;
		}

		void handleInput(Game2D & game, Actor & actor, float dt)
		{
			//if (game.isKeyPressed(GLFW_KEY_UP))				button_up->execute(actor, dt);
			//else if (game.isKeyPressed(GLFW_KEY_DOWN))		button_down->execute(actor, dt);
			//else if (game.isKeyPressed(GLFW_KEY_RIGHT))		button_right->execute(actor, dt);
			//else if (game.isKeyPressed(GLFW_KEY_LEFT))		button_left->execute(actor, dt);
			//else if (game.isKeyPressedAndReleased(GLFW_KEY_SPACE))		button_shoot->execute(actor, dt);

			for (auto &m : key_pressedNreleased_command_map)
			{
				if (game.isKeyPressedAndReleased(m.first)) m.second->execute(actor, dt);
			}

			for (auto &m : key_pressed_command_map)
			{
				if (game.isKeyPressed(m.first)) m.second->execute(actor, dt);
			}
		}
	};

	class TankExample : public Game2D
	{
	public:
		MyTank tank;

		InputHandler input_handler;

	public:
		TankExample()
			: Game2D("This is my digital canvas!", 1024, 768, false, 2)
		{
			//key mapping
			input_handler.key_pressed_command_map[GLFW_KEY_UP]		= new UpCommand;
			input_handler.key_pressed_command_map[GLFW_KEY_DOWN]	= new DownCommand;
			input_handler.key_pressed_command_map[GLFW_KEY_RIGHT]	= new RightCommand;
			input_handler.key_pressed_command_map[GLFW_KEY_LEFT]	= new LeftCommand;
			input_handler.key_pressedNreleased_command_map[GLFW_KEY_SPACE]	= new ShootCommand;

			// key binding
			//std::ifstream textFile("key_binding.txt");
			//std::map<std::string, std::string> key_binding_map;

			//if (textFile)
			//{
			//	std::string str;
			//	while (!textFile.eof())
			//	{
			//		getline(textFile, str);

			//		int current = str.find(' ');
			//		if (current > 0)
			//		{
			//			std::string key = str.substr(0, current);
			//			std::string command = str.substr(current + 1);

			//			// ...
			//		}
			//		else
			//			break;
			//	}
			//}
		}

		~TankExample()
		{}

		void update() override
		{
			// remove a cannon ball
			tank.bullets.erase(std::remove_if(tank.bullets.begin(), tank.bullets.end()
				, [](auto &bullet) {return (bullet != nullptr) && (bullet->center.x > 1.5f); })
				, tank.bullets.end());

			// move tank
			input_handler.handleInput(*this, tank, getTimeStep());

			// move bullet
			for (auto &bullet : tank.bullets)
			{
				if (bullet != nullptr) bullet->update(getTimeStep());
			}

			// rendering
			tank.draw();
			for (auto &bullet : tank.bullets)
			{
				if (bullet != nullptr) bullet->draw();
			}
		}
	};
}