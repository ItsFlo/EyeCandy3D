#pragma once
#include "EC3D/Common/Common.h"

struct GLFWwindow;

namespace ec
{
	/**
	* Enumeration entries for every kind of input event
	*/
	enum class EC3D_DECLSPEC InputType : unsigned char
	{
		mouse_move = 0,
		mouse_scroll,
		mouse_enter,
		mouse_left,
		mouse_button_pressed,
		mouse_button_released,

		joystick,

		key_pressed,
		key_released,
		text,

		drop,
		resize,
		lost_focus,
		gained_focus,
		closed,

		count // Keep at end! - Number of event types
	};

	enum class EC3D_DECLSPEC DisplayOrientation
	{
		rotated_0,
		rotated_90,
		rotated_180,
		rotated_270,
		face_up,
		face_down
	};

	struct EC3D_DECLSPEC DisplayEvent
	{
		explicit DisplayEvent();
		explicit DisplayEvent(GLFWwindow* window,
							  int x, int y,
							  int width, int height,
							  DisplayOrientation orientation = DisplayOrientation::rotated_0);

		void print() const;

		GLFWwindow* m_window;

		int m_x;
		int m_y;
		int m_width;
		int m_height;
		DisplayOrientation m_orientation;
	};

	struct EC3D_DECLSPEC KeyboardEvent
	{
		explicit KeyboardEvent();
		explicit KeyboardEvent(GLFWwindow* window,
							   int key,
							   int scancode,
							   unsigned int unicode,
							   int mods,
							   bool repeat);
		~KeyboardEvent();

		void print() const;

		GLFWwindow* m_window;
		int m_key;
		int m_scancode;
		unsigned int m_unicode;
		int m_mods;
		bool m_repeat;

		bool shiftPressed() const;
		bool controlPressed() const;
		bool altPressed() const;
		bool superPressed() const;
	};

	struct EC3D_DECLSPEC MouseEvent
	{
		explicit MouseEvent();
		explicit MouseEvent(GLFWwindow* window,
							int x, int y, int z, int w,
							int dx, int dy, int dz, int dw,
							unsigned int button,
							int modifier,
							float pressure = 1.0f);
		~MouseEvent();

		void print() const;

		GLFWwindow* m_window;
		int m_x; // primary x position
		int m_y; // primary y position
		int m_z; // mouse wheel position
		int m_w; // (m_w, m_z) mouse wheel position if 2D mouse ball is used

		// Differences since last MouseEvent
		int m_dx;
		int m_dy;
		int m_scrollX;
		int m_scrollY;

		unsigned int m_button;
		int m_mods;

		// For stylus: [0,1]
		// For mouse: {0,1}
		float m_pressure;

		bool shiftPressed() const;
		bool controlPressed() const;
		bool altPressed() const;
		bool superPressed() const;
	};

	struct EC3D_DECLSPEC JoystickEvent
	{
		explicit JoystickEvent();
		explicit JoystickEvent(GLFWwindow* window, int joystick, int event);
		~JoystickEvent();

		void print() const;

		GLFWwindow* m_window;
		int m_joystick;
		int m_event;
	};

	struct EC3D_DECLSPEC DropEvent
	{
		explicit DropEvent();
		explicit DropEvent(int x, int y,
						   GLFWwindow* window, 
						   int count,
						   const char** paths);
		~DropEvent();

		void print() const;

		GLFWwindow* m_window;
		
		// Mouse position
		int m_x;
		int m_y;

		// Number of paths and the paths themselves
		int m_count;
		const char** m_paths;
	};

	union EC3D_DECLSPEC EventData
	{
		explicit EventData();
		~EventData();

		DisplayEvent m_display;
		KeyboardEvent m_keyboard;
		MouseEvent m_mouse;
		JoystickEvent m_joystick;
		DropEvent m_drop;
	};

	/**
	* Group all input events to make transfer easy and save memory 
	* by only holding the event, which is currently active
	*/
	struct EC3D_DECLSPEC InputEvent
	{
		explicit InputEvent();
		explicit InputEvent(InputType type);

		/** Print the currently active event */
		void print() const;

		/** Tells which event is currently active */
		InputType m_type;

		/** */
		double m_timestamp;

	
		EventData m_event;
	};
}