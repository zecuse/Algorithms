#include <DeltaTime/Ticker.hpp>
#include <Timepiece/Stopwatch.hpp>
#include <iostream>

using namespace std;
using namespace Timepiece;
using dtt = DeltaTime::Ticker;

dtt::Ticker()
{

}

void dtt::TickerTest()
{
	Stopwatch sw;
	cout << "here" << endl;
	sw.Start();
}
