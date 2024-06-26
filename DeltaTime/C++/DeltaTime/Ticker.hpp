﻿#pragma once
#include <DeltaTime/Updatable.hpp>
#include <Timepiece/Stopwatch.hpp>
#include <Timepiece/TimeSpan.hpp>
#include <set>

namespace DeltaTime
{
class Ticker
{
	Timepiece::Stopwatch timer = {};
	Timepiece::secs prevTime = {};
	Timepiece::secs offsetTime = {};
public:
	std::multiset<Updatable*> Updatables = {};
	inline bool IsRunning() const
	{ return timer.IsRunning(); }
	void Start();
	void Restart();
	void Pause();
	void Reset();
	Timepiece::secs GetElapsed() const;
	void Offset(const Timepiece::TimeSpan&);
	void ReceiveUpdatable(DeltaTime::Updatable*);
	void PerformTick();
};
}
