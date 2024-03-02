#include <DeltaTime/Ticker.hpp>
#include <iostream>

using namespace std;
using namespace DeltaTime;

int main()
{
	cout << "Hello CMake." << endl;
	Updatable up;
	Ticker ti;
	ti.ReceiveUpdatable(up);
	return 0;
}
