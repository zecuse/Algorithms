#include <Concurrent/Queue.hpp>
#include <DeltaTime/Ticker.hpp>
#include <C++Utilities/stringUtils.hpp>
#include <examples/TickerDemo1.hpp>
#include <examples/TickerDemo2.hpp>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <stop_token>
#include <thread>
#include <re2/re2.h>

using namespace std;
using namespace Concurrent;
using namespace DeltaTime;
using namespace TickerDemo;
using namespace Timepiece;
using namespace StringUtils;

struct ConcurrentData
{
	Queue<Updatable*> AddUpdatables = {};
	Queue<TimeSpan> AddOffset = {};
};

static void PrintMenu(int opt = 1)
{
	switch (opt)
	{
	case 1:
		cout << "Options include:\n";
		cout << "quit: Stop all execution\n";
		cout << "add: Add an Updatable to the ticker\n";
		cout << "offset: Add an offset time to the ticker\n";
		cout << "help: Reprint this list";
		break;
	case 2:
		cout << "1 for Demo1\n";
		cout << "2 for Demo2";
		break;
	case 3:
		cout << "Provide an offset time, negative values allowed, at least 1 duration unit\n";
		cout << "Allowed units: days(d), hours(h), minutes(min), seconds(s), milliseconds(mil), microseconds(mic)";
		break;
	}
	cout << endl;
}

static void UserInput(stop_source src, ConcurrentData &data)
{
	RE2 pattern(R"((-?\d+)(\p{L}+))");
	string input;

	while (getline(cin, input))
	{
		input = trim(toLower(input));
		if (input == "help")
			PrintMenu(1);
		else if (input == "quit")
		{
			src.request_stop();
			cout << "Quitting" << endl;
			break;
		}
		else if (input == "add")
		{
			PrintMenu(2);
			string choice;
			getline(cin, choice);
			choice = trim(choice);
			if (choice == "1")
			{
				TickerDemo1 *demo = new TickerDemo1();
				if (!data.AddUpdatables.push(demo, 1s))
					delete demo;
			}
			else if (choice == "2")
			{
				TickerDemo2 *demo = new TickerDemo2();
				if (!data.AddUpdatables.push(demo, 1s))
					delete demo;
			}
			else
				cout << choice << " is not an option.\n";
		}
		else if (input == "offset")
		{
			PrintMenu(3);
			string time;
			getline(cin, time);

			absl::string_view matches(time);
			int d = 0, h = 0, min = 0, s = 0, mil = 0, mic = 0;
			int val = 0;
			string unit = "";
			while (RE2::FindAndConsume(&matches, pattern, &val, &unit))
			{
				if (unit.starts_with('d'))
					d = val;
				else if (unit.starts_with('h'))
					h = val;
				else if (unit.starts_with("min"))
					min = val;
				else if (unit.starts_with('s'))
					s = val;
				else if (unit.starts_with("mil"))
					mil = val;
				else if (unit.starts_with("mic"))
					mic = val;
			}

			TimeSpan offset = { .days = dayt{d}, .hours = hrt{h}, .minutes = mint{min}, .seconds = sect{s}, .millis = milt{mil}, .micros = mict{mic} };
			data.AddOffset.push(offset, 1s);
		}
	}
}

static void DoTicking(stop_token tkn, ConcurrentData &data)
{
	Ticker ticker = {};
	Updatable *updatable = {};
	TimeSpan span = {};

	while (true)
	{
		if (tkn.stop_requested())
		{
			ticker.Pause();
			cout << "Execution done" << endl;
			break;
		}
		while (data.AddUpdatables.pop(updatable, 1s))
		{
			ticker.ReceiveUpdatable(updatable);
			if (!ticker.IsRunning())
				ticker.Start();
		}
		if (!ticker.Updatables.empty())
		{
			while (data.AddOffset.pop(span, 1s))
				ticker.Offset(span);
			ticker.PerformTick();
		}
		this_thread::sleep_for(1s);
	}
}

int main()
{
	stop_source src;
	ConcurrentData data;
	PrintMenu(1);
	jthread ui(UserInput, src, ref(data));
	jthread tick(DoTicking, src.get_token(), ref(data));
	return 0;
}
