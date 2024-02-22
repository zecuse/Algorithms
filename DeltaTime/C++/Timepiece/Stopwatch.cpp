#include <Timepiece/Stopwatch.hpp>
#include <iostream>

using namespace std;
using tsw = Timepiece::Stopwatch;

tsw::Stopwatch()
{

}

void tsw::Start()
{
	cout << "Stopwatch started" << endl;
}
