#pragma once
#include "EC3D/Common/Common.h"
#include "InputEvent.h"

#include <vector>

/**
* InputObservables inform InputListeners about InputEvents
*/
namespace ec
{
	class InputListener;

	class EC3D_DECLSPEC InputObservable
	{
	public:
		using InputListeners_Type = std::vector<InputListener*>;
		using Events_Type = std::vector<InputEvent>;


		explicit InputObservable();
		virtual ~InputObservable();

		/* *
		* Inform the listeners about a new event
		* The input listener can't check for inputs itself because of the way GLFW works
		*/
		virtual void receiveEvent(const InputEvent& event);

		/** Register a new or remove an old listener */
		virtual void registerInputListener(InputListener* inputListener);
		virtual bool unregisterInputListener(InputListener* inputListener);

		/** Check if this observer contains a specific controller */
		virtual bool contains(InputListener* inputListener);

		/** Clears the input listener list */
		virtual void unregisterAllInputListeners();

		/** Inform all input listeners about all accumulated events */
		virtual void informAll();

		/** Set the previous mouse event */
		void setPrevMouseEvent(const MouseEvent& event);
		/** Get the previous mouse event */
		const MouseEvent& getPrevMouseEvent() const;

		/** Set the previous keyboard event */
		void setPrevKeyboardEvent(const KeyboardEvent& event);
		/** Get the previous keyboard event */
		const KeyboardEvent& getPrevKeyboardEvent() const;

		/** Set the previous keyboard event */
		void setPrevDisplayEvent(const DisplayEvent& event);
		/** Get the previous keyboard event */
		const DisplayEvent& getPrevDisplayEvent() const;

	protected:

		InputEvent prepareEvent(const InputEvent& event);

		InputListeners_Type m_inputListeners;
		Events_Type m_events;

		/** Previous mouse event */
		MouseEvent m_prevMouseEvent;
		/** Previous keyboard event */
		KeyboardEvent m_prevKeyboardEvent;
		/** Previous display event */
		DisplayEvent m_prevDisplayEvent;

		virtual void clearEvents();
	};
}