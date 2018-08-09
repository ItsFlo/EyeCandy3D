#include "EC3D/Utilities/Profiler.h"

#include <chrono>

namespace utl
{
	namespace
	{
		unsigned int EvaluateProfilingPrecision(std::chrono::steady_clock::time_point start,
										 std::chrono::steady_clock::time_point end,
										 ProfilingPrecision precision)
		{
			using namespace std::chrono;

			switch(precision)
			{
				case ProfilingPrecision::second:
					return static_cast<unsigned int>(duration_cast<seconds>(end - start).count());
					break;
				case ProfilingPrecision::millisecond:
					return static_cast<unsigned int>(duration_cast<milliseconds>(end - start).count());
					break;
				case ProfilingPrecision::microsecond:
					return static_cast<unsigned int>(duration_cast<microseconds>(end - start).count());
					break;
				case ProfilingPrecision::nanosecond:
					return static_cast<unsigned int>(duration_cast<nanoseconds>(end - start).count());
					break;

				default:
					printf("ERROR Profiler: precision not defined!\n");
					return static_cast<unsigned int>(duration_cast<seconds>(end - start).count());
					break;
			}
		}	
	}

	void ProfilingData::Print()
	{
		printf("Number of executions: %d\n", m_loops);
		if(m_loops > 1)
		{
			printf("Time taken:\n");
			printf("- min: %d%s\n", m_min, m_precisionPostfix.c_str());
			printf("- max: %d%s\n", m_max, m_precisionPostfix.c_str());
			printf("- avg: %d%s\n", m_avg, m_precisionPostfix.c_str());
		}
		else
		{
			printf("Time taken: %d%s\n", m_min, m_precisionPostfix.c_str());
		}
	}

	void ProfilingData::SetPrecision(ProfilingPrecision precision)
	{
		m_precision = precision;

		switch(precision)
		{
			case ProfilingPrecision::second:
				m_precisionPostfix = "s";
				break;
			case ProfilingPrecision::millisecond:
				m_precisionPostfix = "ms";
				break;
			case ProfilingPrecision::microsecond:
				m_precisionPostfix = "us";
				break;
			case ProfilingPrecision::nanosecond:
				m_precisionPostfix = "ns";
				break;
			default:
				m_precisionPostfix = "";
				break;

		}
	}

	utl::ProfilingPrecision ProfilingData::GetPrecision() const
	{
		return m_precision;
	}

	ProfilingData ProfileFunction(std::function<void(void)> f,
								  const unsigned int loops,
								  ProfilingPrecision precision)
	{
		ProfilingData data;
		data.m_loops = loops;
		data.SetPrecision(precision);

		unsigned int tempMin = UINT_MAX;
		unsigned int tempMax = 0;
		unsigned int tempAvg = 0;

		for(int i = 0; i < loops; ++i)
		{
			auto start = std::chrono::high_resolution_clock::now();
			f();
			auto end = std::chrono::high_resolution_clock::now();
			auto timeTaken = EvaluateProfilingPrecision(start, end, precision);

			tempAvg += timeTaken;

			tempMin = tempMin < timeTaken ? tempMin : timeTaken;
			tempMax = tempMax > timeTaken ? tempMax : timeTaken;
		}

		data.m_min = tempMin;
		data.m_max = tempMax;
		data.m_avg = tempAvg / data.m_loops;
		
		return data;
	}
}