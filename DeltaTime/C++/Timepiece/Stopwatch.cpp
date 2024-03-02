#include <Timepiece/Stopwatch.hpp>
#include <iostream>

using namespace std;
using tsw = Timepiece::Stopwatch;

void Timepiece::Stopwatch::Start()
{
	if (!IsRunning())
		StartTime = steady_clock::now();
}

void Timepiece::Stopwatch::Restart()
{
	StartTime = steady_clock::now();
	ElapsedTime = {};
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
}

Timepiece::seconds Timepiece::Stopwatch::GetElapsed() const
{
	auto result = ElapsedTime;
	if (IsRunning())
		result += steady_clock::now() - StartTime;
	return result;
}
