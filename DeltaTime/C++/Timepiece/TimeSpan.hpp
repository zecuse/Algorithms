#pragma once
#include <chrono>

namespace Timepiece
{
using namespace std;
using namespace chrono;
typedef duration<double> sec;
typedef duration<double, ratio_multiply<ratio<60>, sec::period>> min;
typedef duration<double, ratio_multiply<ratio<60>, min::period>> hr;
typedef duration<double, ratio_multiply<ratio<24>, hr::period>> day;
typedef duration<double, ratio_multiply<sec::period, ratio<1000>>> mil;
typedef duration<double, ratio_multiply<mil::period, ratio<1000>>> mic;
typedef duration<double, ratio_multiply<mic::period, ratio<1000>>> na;

struct TimeSpan
{
	day days{ 0 };
	hr hours{ 0 };
	min minutes{ 0 };
	sec seconds{ 0 };
	mil millis{ 0 };
	mic micros{ 0 };
	na nanos{ 0 };
	inline sec Count() const
	{ return days + hours + minutes + seconds + millis + micros + nanos; }
};
}
