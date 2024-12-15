#include <conio.h>
#include <iostream>
#include "World.h"

using namespace PhysModel;

void UpdateLoop(World& world, int refresh_rate)
{
	world.UpdateLoop(refresh_rate);
}

void Input(World& world, char input)
{
	char new_input;

	switch (input)
	{
	case '1':
	projectile_motion:
		system("CLS");
		PhysModel::sim_type = '1';
		PhysModel::camera.ResetPosition();
		std::cout << "Please press 'c' to create a new projectile or '2' to switch to Celestial Motion" << std::endl;
		new_input = _getch();
		while (new_input != 'c' && new_input != '2')
		{
			new_input = _getch();
		}

		if (new_input == 'c')
		{
			std::string x_char = "";
			float x;

		x_p_input:
			std::cout << "Enter x co-ordinate : " << std::endl;
			std::cin >> x_char;

			try
			{
				x = atof(x_char.c_str());
			}
			catch (std::exception)
			{
				std::cout << "Please enter a valid x co-ordinate!" << std::endl;
				goto x_p_input;
			}

			std::string y_char = "";
			float y;

		y_p_input:
			std::cout << "Enter y co-ordinate : " << std::endl;
			std::cin >> y_char;

			try
			{
				y = atof(y_char.c_str());
			}
			catch (std::exception)
			{
				std::cout << "Please enter a valid y co-ordinate!" << std::endl;
				goto y_p_input;
			}

			std::string initial_velocity_char = "";
			float initial_velocity;

		velocity_p_input:
			std::cout << "Enter velocity : " << std::endl;
			std::cin >> initial_velocity_char;

			try
			{
				initial_velocity = atof(initial_velocity_char.c_str());
			}
			catch (std::exception)
			{
				std::cout << "Please enter a valid velocity!" << std::endl;
				goto velocity_p_input;
			}

			std::string angle_char = "";
			float angle;

		angle_input:
			std::cout << "Enter velocity angle (in degrees) : " << std::endl;
			std::cin >> angle_char;

			try
			{
				angle = atof(angle_char.c_str());
			}
			catch (std::exception)
			{
				std::cout << "Please enter a valid velocity angle!" << std::endl;
				goto angle_input;
			}

			std::string gravity_char = "";
			float gravity;

		gravity_input:
			std::cout << "Enter acceleration due to gravity on this projectile : " << std::endl;
			std::cin >> gravity_char;

			try
			{
				gravity = atof(gravity_char.c_str());
			}
			catch (std::exception)
			{
				std::cout << "Please enter a valid acceleration!" << std::endl;
				goto gravity_input;
			}

			world.projectile_motion.CreateProjectile(Position(x, y), initial_velocity, 0, 0, angle, 0, gravity);
			goto projectile_motion;
		}
		else if (new_input == '2')
		{
			goto celestial_motion;
		}

		break;
	case '2':
	celestial_motion:
		system("CLS");
		PhysModel::sim_type = '2';
		PhysModel::camera.ResetPosition();
		std::cout << "Please press 'c' to create a new celestial body or '1' to switch to Projectile Motion" << std::endl;
		new_input = _getch();
		while (new_input != 'c' && new_input != '1')
		{
			new_input = _getch();
		}

		if (new_input == 'c')
		{
			std::string x_char = "";
			float x;

		x_c_input:
			std::cout << "Enter x co-ordinate : " << std::endl;
			std::cin >> x_char;

			try
			{
				x = atof(x_char.c_str());
			}
			catch (std::exception)
			{
				std::cout << "Please enter a valid x co-ordinate!" << std::endl;
				goto x_c_input;
			}

			std::string y_char = "";
			float y;

		y_c_input:
			std::cout << "Enter y co-ordinate : " << std::endl;
			std::cin >> y_char;

			try
			{
				y = atof(y_char.c_str());
			}
			catch (std::exception)
			{
				std::cout << "Please enter a valid y co-ordinate!" << std::endl;
				goto y_c_input;
			}

			std::string initial_velocity_char = "";
			float initial_velocity;

		velocity_c_input:
			std::cout << "Enter velocity : " << std::endl;
			std::cin >> initial_velocity_char;

			try
			{
				initial_velocity = atof(initial_velocity_char.c_str());
			}
			catch (std::exception)
			{
				std::cout << "Please enter a valid velocity!" << std::endl;
				goto velocity_c_input;
			}

			std::string radius_char = "";
			float radius;

		radius_input:
			std::cout << "Enter radius : " << std::endl;
			std::cin >> radius_char;

			try
			{
				radius = atof(radius_char.c_str());
			}
			catch (std::exception)
			{
				std::cout << "Please enter a valid radius!" << std::endl;
				goto radius_input;
			}

			std::string mass_char = "";
			float mass;

		mass_input:
			std::cout << "Enter mass : " << std::endl;
			std::cin >> mass_char;

			try
			{
				mass = atof(mass_char.c_str());
			}
			catch (std::exception)
			{
				std::cout << "Please enter a valid mass!" << std::endl;
				goto mass_input;
			}

			std::string r_char = "";
			float r;

		r_input:
			std::cout << "Enter red colour value : " << std::endl;
			std::cin >> r_char;

			try
			{
				r = atof(r_char.c_str());

				if (r < 0 || r > 255)
				{
					std::cout << "Please enter a valid red colour value!" << std::endl;
					goto r_input;
				}
			}
			catch (std::exception)
			{
				std::cout << "Please enter a valid red colour value!" << std::endl;
				goto r_input;
			}

			std::string g_char = "";
			float g;

		g_input:
			std::cout << "Enter green colour value : " << std::endl;
			std::cin >> g_char;

			try
			{
				g = atof(g_char.c_str());

				if (g < 0 || g > 255)
				{
					std::cout << "Please enter a valid green colour value!" << std::endl;
					goto g_input;
				}
			}
			catch (std::exception)
			{
				std::cout << "Please enter a valid green colour value!" << std::endl;
				goto g_input;
			}

			std::string b_char = "";
			float b;

		b_input:
			std::cout << "Enter blue colour value : " << std::endl;
			std::cin >> b_char;

			try
			{
				b = atof(b_char.c_str());

				if (b < 0 || b > 255)
				{
					std::cout << "Please enter a valid blue colour value!" << std::endl;
					goto b_input;
				}
			}
			catch (std::exception)
			{
				std::cout << "Please enter a valid blue colour value!" << std::endl;
				goto b_input;
			}

			world.celestial_motion.CreateBody(Position(x, y), radius, mass, initial_velocity, al_map_rgb(r, g, b));
			goto celestial_motion;
		}
		else if (new_input == '1')
		{
			goto projectile_motion;
		}

		break;
	}
}

int main()
{
	std::cout << "Welcome To Physics Simulation" << std::endl << "Please press '1' to switch to Projectile Motion, '2' to switch to Celestial Motion" << std::endl;

	char input = _getch();
	while (input != '1' && input != '2')
	{
		input = _getch();
	}

	World world = World();

	world.CreateProjectileMotion();
	world.CreateCelestialMotion();

	std::thread world_thread(UpdateLoop, std::ref(world), 240);
	world_thread.detach();

	std::thread input_thread(Input, std::ref(world), input);
	input_thread.detach();

	while (!PhysModel::close)
	{

	}
}