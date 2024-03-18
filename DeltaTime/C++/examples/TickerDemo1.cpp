#include <examples/TickerDemo1.hpp>
#include <format>
#include <iomanip>
#include <iostream>

using namespace std;

void TickerDemo::TickerDemo1::Update(double deltaTime)
{
	string str = format("{}: {:10.6f}\n", "TickerDemo1", deltaTime);
	cout.setf(ios::right, ios::adjustfield);
	cout.width(60);
	cout << right << setw(60) << str;
}
