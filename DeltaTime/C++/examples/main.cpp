#include <Concurrent/Queue.hpp>
#include <DeltaTime/Ticker.hpp>
#include <iostream>
#include <stop_token>
#include <thread>

using namespace std;

void UserInput(stop_source src)
{
	cout << "user input started\n";
	string input;
	while (getline(cin, input))
	{
		if (input == "quit")
		{
			src.request_stop();
			break;
		}
		cout << "getting next input\n";
	}
	cout << "user input ended" << endl;
}

void DoTicking(stop_token tkn)
{
	cout << "ticking started\n";
	while (true)
	{
		if (tkn.stop_requested())
		{
			break;
		}
		cout << "tick\n";
		this_thread::sleep_for(1s);
	}
	cout << "ticking ended" << endl;
}

int main()
{
	stop_source source;
	jthread ui(UserInput, source);
	jthread tick(DoTicking, source.get_token());
	cout << "[main] bye!!" << endl;
	return 0;
}
