/***************************************
 *  @file    Stopwatch.hpp
 *  @brief   A data structure that steadily tracks the passage of time.
 **************************************/
#pragma once
#include <Timepiece/TimeSpan.hpp>
#include <chrono>

namespace Timepiece
{
using steady_clock = std::chrono::steady_clock;

/***************************************
 *  @class   Stopwatch
 *  @brief   A data structure that steadily tracks the passage of time.
 *  @details This structure uses chrono's steady_clock interface to
 * monotonically track time.
 **************************************/
class Stopwatch
{
	steady_clock::time_point StartTime = {};
	secs ElapsedTime = {};
	std::vector<secs> LapTimes = {};

public:
	/** @addtogroup Stopwatch_Controls Controls for a Stopwatch
	 *  @brief   All of the basic controls found on a stopwatch.
	 *  @{
	 */
	void Start();
	void Lap();
	void Restart();
	void Pause();
	void Reset();
	/**@}*/
	inline bool IsRunning() const
	{ return StartTime != steady_clock::time_point{}; }
	secs GetElapsed() const;
	inline std::vector<secs> GetLaps() const
	{ return LapTimes; }
};
}
