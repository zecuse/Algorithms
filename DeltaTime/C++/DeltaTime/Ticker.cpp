#include <DeltaTime/Ticker.hpp>
#include <iostream>

using namespace std;
using namespace Timepiece;

void DeltaTime::Ticker::Start()
{
	timer.Start();
}

void DeltaTime::Ticker::Restart()
{
	timer.Restart();
}

void DeltaTime::Ticker::Pause()
{
	timer.Pause();
}

void DeltaTime::Ticker::Reset()
{
	timer.Reset();
}

Timepiece::seconds DeltaTime::Ticker::GetElapsed() const
{
	return timer.GetElapsed();
}

void DeltaTime::Ticker::Offset(const TimeSpan &span)
{
	offsetTime += span.Count();
}

void DeltaTime::Ticker::ReceiveUpdatable(DeltaTime::Updatable updatable)
{
	if (Updatables.empty())
		Updatables.insert(updatable);
	else if (*(Updatables.rbegin()) < updatable)
		Updatables.insert(Updatables.end(), updatable);
	else if (updatable < *(Updatables.begin()))
		Updatables.insert(Updatables.begin(), updatable);
	else
		Updatables.insert(updatable);
}

void DeltaTime::Ticker::PerformTick()
{
	auto now = timer.GetElapsed();
	Timepiece::seconds deltaTime = now - prevTime + offsetTime;
	offsetTime = {};

	for (auto &updatable : Updatables)
		const_cast<Updatable &>(updatable).Update(deltaTime.count());
	prevTime = timer.GetElapsed();
}
