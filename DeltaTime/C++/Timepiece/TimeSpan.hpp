#pragma once
#include <chrono>

namespace Timepiece
{
using namespace std;
using namespace chrono;
typedef duration<double> sect;
typedef duration<double, ratio_multiply<ratio<60>, sect::period>> mint;
typedef duration<double, ratio_multiply<ratio<60>, mint::period>> hrt;
typedef duration<double, ratio_multiply<ratio<24>, hrt::period>> dayt;
typedef duration<double, ratio_multiply<sect::period, ratio<1000>>> milt;
typedef duration<double, ratio_multiply<milt::period, ratio<1000>>> mict;
typedef duration<double, ratio_multiply<mict::period, ratio<1000>>> nant;

struct TimeSpan
{
	dayt days{ 0 };
	hrt hours{ 0 };
	mint minutes{ 0 };
	sect seconds{ 0 };
	milt millis{ 0 };
	mict micros{ 0 };
	nant nanos{ 0 };
	inline sect Count() const
	{ return days + hours + minutes + seconds + millis + micros + nanos; }
};
}
