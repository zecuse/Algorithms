#include <Timepiece/Stopwatch.hpp>
#include <iostream>

using namespace std;

void Timepiece::Stopwatch::Start()
{
	if (!IsRunning())
		StartTime = steady_clock::now();
}

void Timepiece::Stopwatch::Lap()
{
	LapTimes.push_back(steady_clock::now() - StartTime);
}

void Timepiece::Stopwatch::Restart()
{
	StartTime = steady_clock::now();
	ElapsedTime = {};
	LapTimes = {};
}

void Timepiece::Stopwatch::Pause()
{
	ElapsedTime += steady_clock::now() - StartTime;
	StartTime = {};
}

void Timepiece::Stopwatch::Reset()
{
	StartTime = {};
	ElapsedTime = {};
	LapTimes = {};
}

Timepiece::secs Timepiece::Stopwatch::GetElapsed() const
{
	auto result = ElapsedTime;
	if (IsRunning())
		result += steady_clock::now() - StartTime;
	return result;
}
