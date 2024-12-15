#pragma once
#include <vector>
#include <math.h>
#include <windows.h>
#include "Properties.h"

namespace PhysModel
{
	class ProjectileMotion
	{
	public:
		class Projectile
		{
		public:
			Projectile(Position pos, float ini_v, float acc, float dis, float dir_v, float dir_a, float grav)
			{
				position_w = pos;
				initial_v = ini_v;
				working_v = initial_v;
				acceleration = acc;
				displacement = dis;
				direction_v_r = dir_v * (ALLEGRO_PI / 180);
				direction_a_r = dir_a * (ALLEGRO_PI / 180);
				gravity = grav;
				working_v_h = roundf(working_v * cos(direction_v_r) * 1000) / 1000;
				working_v_v = roundf(working_v * sin(direction_v_r) * 1000) / 1000;
				acceleration_h = roundf(acceleration * cos(direction_a_r) * 1000) / 1000;
				acceleration_v = (roundf(acceleration * sin(direction_a_r) * 1000) / 1000) - gravity;
			}

			void SetVelocity(float new_ini_v, float new_dir_v)
			{
				initial_v = new_ini_v;
				working_v = initial_v;
				direction_v_r = new_dir_v * (ALLEGRO_PI / 180);
				working_v_h = roundf(working_v * cos(direction_v_r) * 1000) / 1000;
				working_v_v = roundf(working_v * sin(direction_v_r) * 1000) / 1000;
			}

			void EnableGravity(float grav)
			{
				gravity = grav;
				acceleration_v = (roundf(acceleration * sin(direction_a_r) * 1000) / 1000) - gravity;
			}

			void SetAcceleration(float new_acc, float new_dir_a)
			{
				acceleration = new_acc;
				direction_a_r = new_dir_a * (ALLEGRO_PI / 180);
				acceleration_h = roundf(acceleration * cos(direction_a_r) * 1000) / 1000;
				acceleration_v = (roundf(acceleration * sin(direction_a_r) * 1000) / 1000) - gravity;
			}

			void UpdatePosition(double time)
			{
				working_v_h += acceleration_h * time;
				working_v_v += acceleration_v * time;

				float displacement_h = working_v_h * time;
				float displacement_v = working_v_v * time;

				position_w.x += displacement_h;
				position_w.y += displacement_v;

				Graphics::DrawFilledCircle(position_w.x, position_w.y, 10, blue);
			}

			Position position_w;
			float initial_v;
			float working_v;
			float working_v_h = 0.0f;
			float working_v_v = 0.0f;
			float acceleration;
			float acceleration_h = 0.0f;
			float acceleration_v = 0.0f;
			float displacement;
			float direction_v_r;
			float direction_a_r;
			float gravity;
			float mass;
			float area;
			ALLEGRO_COLOR blue = al_map_rgb(44, 117, 225);
		};

		void UpdateProjectiles(std::chrono::microseconds render_lag)
		{
			Graphics::ClearScreen();
			double time_m = ((double)render_lag.count() / 1000000);

			for (Projectile& proj : projectiles_a)
			{
				proj.UpdatePosition(time_m);
			}
			total_time += time_m;
			Graphics::UpdateScreen();
		}

		double total_time = 0;
		std::vector<Projectile> projectiles_a;

		int CreateProjectile(Position pos = Position(0, 0), float ini_v = 0, float acc = 0, float dis = 0, float dir_v = 0, float dir_a = 0, float gravity = 0)
		{
			Projectile projectile_n = Projectile(pos, ini_v, acc, dis, dir_v, dir_a, gravity);
			projectiles_a.push_back(projectile_n);
			return projectiles_a.size() - 1;
		}
	};
}