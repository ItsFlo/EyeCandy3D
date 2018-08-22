#pragma once

/*
* Track the time passed since the timer was initialized last
* and the time between calls.
*/
namespace ec
{
	class Timer
	{
	public:
		explicit Timer();
		~Timer();

		/** Reset the whole timer */
		void reset();

		/** Only reset the time since the last access of time delta */
		void resetTimeDelta();

		/** Get time since the start of the timer or last reset */
		double getTime() const;
		/** Get time between calls */
		double getTimeDelta();

	private:
		double m_start{};

		double m_timeDeltaFirst{};
		double m_timeDeltaLast{};
	};
}