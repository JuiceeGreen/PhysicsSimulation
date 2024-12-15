#pragma once
#include <vector>
#include <math.h>
#include <windows.h>
#include <algorithm>
#include "Properties.h"

namespace PhysModel
{
	const double gravitational_constant = 0.000667;
	int cbodies_n = 0;

	class CelestialMotion
	{
	public:
		class CBody
		{
		public:
			CBody(Position pos, float new_radius, float new_mass, double new_f_velocity, ALLEGRO_COLOR new_colour)
			{
				position_w = pos;
				radius = new_radius;
				mass = new_mass;
				velocity_y = new_f_velocity;
				colour = new_colour;
			}

			double Clamp(double value, double min, double max)
			{
				if (value < min) value = min;
				if (value > max) value = max;
				return value;
			}

			void HandleCollision(int cbody_id, std::vector<CBody>& cbodies_a)
			{
				CBody cbody = cbodies_a[cbody_id];
				velocity_x = ((cbody.mass * cbody.velocity_x) + (mass * velocity_x)) / (mass + cbody.mass);
				mass += cbody.mass;
				if (cbody.radius > radius)
				{
					radius = cbody.radius + (radius / 2);
				}
				else
				{
					radius += (cbody.radius / 2);
				}

				colour = al_map_rgb(Clamp(colour.r + cbody.colour.r, 0, 255), Clamp(colour.g + cbody.colour.g, 0, 255), Clamp(colour.b + cbody.colour.b, 0, 255));

				cbodies_a.erase(cbodies_a.begin() + cbody_id);
				cbodies_n -= 1;
			}

			void CalculateMotion(std::vector<CBody>& cbodies_a, double time, float time_scale)
			{
				int i = 0;
				for (CBody& cbody : cbodies_a)
				{
					if (&cbody != this)
					{
						double displacement_x = cbody.position_w.x - position_w.x;
						double displacement_y = cbody.position_w.y - position_w.y;

						double distance_squared = pow(displacement_x, 2) + pow(displacement_y, 2);
						double distance = sqrt(distance_squared);

						if (distance - radius - cbody.radius <= 0)
						{
							HandleCollision(i, cbodies_a);
							continue;
						}

						double theta = atan2(displacement_y, displacement_x);

						double acceleration = (gravitational_constant * cbody.mass) / distance_squared;

						double acceleration_x = acceleration * cos(theta);
						double acceleration_y = acceleration * sin(theta);

						velocity_x += acceleration_x * time;
						velocity_y += acceleration_y * time;
					}

					position_w.x += velocity_x * time_scale * time;
					position_w.y += velocity_y * time_scale * time;
					i++;
				}

				Graphics::DrawFilledCircle(position_w.x, position_w.y, radius, colour);
			}

			Position position_w;
			float radius;
			float mass;
			double velocity_x = 0;
			double velocity_y = 0;
			ALLEGRO_COLOR colour;
		};

		void UpdateBodies(std::chrono::microseconds render_lag)
		{
			Graphics::ClearScreen();
			double time_m = ((double)render_lag.count() / 1000000);

			for (int i = 0; i < cbodies_n; i++)
			{
				cbodies_a[i].CalculateMotion(cbodies_a, time_m, time_scale);
			}
			Graphics::UpdateScreen();
		}

		std::vector<CBody> cbodies_a;
		float time_scale = 10000;

		int CreateBody(Position pos = Position(0, 0), float new_radius = 1, float new_mass = 1, double new_f_velocity = 0, ALLEGRO_COLOR new_colour = al_map_rgb(255, 255, 255))
		{
			CBody cbody_n = CBody(pos, new_radius, new_mass, new_f_velocity / time_scale, new_colour);
			cbodies_a.push_back(cbody_n);
			cbodies_n += 1;
			return cbodies_a.size() - 1;
		}
	};
}