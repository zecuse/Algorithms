#pragma once
#include <chrono>

namespace Timepiece
{
using steady_clock = std::chrono::steady_clock;
using seconds = std::chrono::duration<double>;

class Stopwatch
{
	steady_clock::time_point StartTime = {};
	seconds ElapsedTime = {};

public:
	inline bool IsRunning() const
	{ return StartTime != steady_clock::time_point{}; }
	void Start();
	void Restart();
	void Pause();
	void Reset();
	seconds GetElapsed() const;
};
}
