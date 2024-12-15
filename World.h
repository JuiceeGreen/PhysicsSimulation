#pragma once
#include <thread>
#include <windows.h>
#include "Properties.h"
#include "CelestialMotion.h"
#include "ProjectileMotion.h"

namespace PhysModel
{
	char sim_type = '0';

	class World
	{
	public:
		void UpdateCameraLoop()
		{
			camera.UpdateLoop();
		}

		void UpdateLoop(int refresh_rate)
		{
			Graphics::Initialize();

			std::thread camera_thread(&World::UpdateCameraLoop, this);
			camera_thread.detach();

			if (sim_type != '0')
			{
				while (!close)
				{
					auto start = std::chrono::high_resolution_clock::now();

					if (sim_type == '1')
					{
						projectile_motion.UpdateProjectiles(render_lag);
					}
					else if (sim_type == '2')
					{
						celestial_motion.UpdateBodies(render_lag);
					}

					std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(1000 / refresh_rate));

					auto stop = std::chrono::high_resolution_clock::now();
					render_lag = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
				}
			}
		}

		ProjectileMotion CreateProjectileMotion()
		{
			projectile_motion = ProjectileMotion();
			return projectile_motion;
		}

		CelestialMotion CreateCelestialMotion()
		{
			celestial_motion = CelestialMotion();
			return celestial_motion;
		}

		ProjectileMotion projectile_motion;
		CelestialMotion celestial_motion;
		std::chrono::microseconds render_lag;
	};
}