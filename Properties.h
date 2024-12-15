#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_windows.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

#define WM_MOUSEWHEEL 0x020A

namespace PhysModel
{
	static bool close = false;
	static HWND display_hwnd;

	class Position
	{
	public:
		Position(double new_x = 0, double new_y = 0)
		{
			x = new_x;
			y = new_y;
		}

		double x;
		double y;
	};

	class Camera
	{
	public:
		void UpdateLoop()
		{
			while (!close)
			{
				if (GetKeyState('W') & 0x8000)
				{
					position_w.y -= (1 * camera_speed);
				}
				else if (GetKeyState('S') & 0x8000)
				{
					position_w.y += (1 * camera_speed);
				}
				else if (GetKeyState(VK_UP) & 0x8000)
				{
					position_w.y -= (1 * camera_speed);
				}
				else if (GetKeyState(VK_DOWN) & 0x8000)
				{
					position_w.y += (1 * camera_speed);
				}
				if (GetKeyState('A') & 0x8000)
				{
					position_w.x -= (1 * camera_speed);
				}
				else if (GetKeyState('D') & 0x8000)
				{
					position_w.x += (1 * camera_speed);
				}
				else if (GetKeyState(VK_LEFT) & 0x8000)
				{
					position_w.x -= (1 * camera_speed);
				}
				else if (GetKeyState(VK_RIGHT) & 0x8000)
				{
					position_w.x += (1 * camera_speed);
				}
			}
		}

		void ScrollEvent(int x, int y, int z)
		{
			if (z == 1)
			{
				camera_zoom *= camera_zoom_speed;
			}
			else if (z == -1)
			{
				camera_zoom /= camera_zoom_speed;
			}
			else
			{
				return;
			}
		}
		
		void ResetPosition()
		{
			position_w = Position(640, 360);
		}
		
		float camera_zoom = 1;
		float camera_zoom_speed = 1.01f;
		float camera_speed = 0.003f;
		float total_zoom = 1;
		Position position_w = Position(640, 360);
	};

	static Camera camera = Camera();

	static class Graphics
	{
	public:
		static void Initialize()
		{
			if (!al_init())
			{
				al_show_native_message_box(NULL, NULL, NULL, "Could not initialize", NULL, NULL);
			}

			ALLEGRO_DISPLAY* display = al_create_display(1280, 720);
			al_set_window_title(display, "Physics Simulation");

			display_hwnd = al_get_win_window_handle(display);

			if (!display)
			{
				al_show_native_message_box(display, "Physics Simulation", "Display Settings", "Display window was not created successfully", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			}

			al_init_primitives_addon();
			al_install_mouse();

			std::thread event_thread(EventHandler, display);
			event_thread.detach();
		}

		static void ClearScreen()
		{
			al_clear_to_color(al_map_rgb(0, 0, 0));
		}
#
		static void UpdateScreen()
		{
			al_flip_display();
		}

		static void DrawFilledCircle(float x, float y, float r, ALLEGRO_COLOR colour)
		{
			float scale = camera.camera_zoom;
			float new_x = (x - camera.position_w.x) * scale;
			float new_y = (720 - y - camera.position_w.y) * scale;

			al_draw_filled_circle(new_x + 640, new_y + 360, r * scale, colour);
		}

		static void EventHandler(ALLEGRO_DISPLAY* display)
		{
			ALLEGRO_EVENT_QUEUE* queue;
			queue = al_create_event_queue();
			al_register_event_source(queue, al_get_display_event_source(display));
			al_register_event_source(queue, al_get_mouse_event_source());

			while (true)
			{
				ALLEGRO_EVENT events;
				al_wait_for_event(queue, &events);

				if (events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
				{
					al_destroy_event_queue(queue);
					al_destroy_display(display);
					close = true;
					return;
				}
				else if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
				{
					camera.ScrollEvent(events.mouse.x, events.mouse.y, events.mouse.dz);
				}
			}
		}
	};
}