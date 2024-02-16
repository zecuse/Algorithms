using DeltaTime;
using System.Collections.Concurrent;
using System.Runtime.CompilerServices;
using System.Text;
using System.Text.RegularExpressions;

/// <summary>
/// A simple program to demonstrate the DeltaTime project.
/// </summary>
class Program
{
	/// <summary>
	/// A token source to communitcate between the user input thread and ticking thread.<br/>
	/// </summary>
	static CancellationTokenSource CTS { get; } = new();

	/// <summary>
	/// A factory for creating child threads unified by a single cancellation token.
	/// </summary>
	static TaskFactory Factory { get; } = new(CTS.Token);

	/// <summary>
	/// Create 2 threads:<br/>
	/// 1. Runs the <see cref="Ticker"/><br/>
	/// 2. Handles user input
	/// </summary>
	/// <param name="args">No args needed.</param>
	static void Main(string[] args)
	{
		ConcurrentData data = new();
		Task.WaitAll(
			Factory.StartNew(() => DoTicking(data)),
			Factory.StartNew(() => GetUserInput(data))
		);
		CTS.Dispose();
	}

	/// <summary>
	/// Demonstrate the functionality of the <see cref="Ticker"/> class.
	/// </summary>
	/// <param name="data">Concurrent data received from the user input thread.</param>
	static void DoTicking(ConcurrentData data)
	{
		Ticker ticker = new();

		while (true)
		{
			if (CTS.Token.IsCancellationRequested)
			{
				ticker.Pause();
				Console.WriteLine("Execution done");
				break;
			}
			while (data.AddUpdatables.TryDequeue(out Updatable updatable))
			{
				ticker.ReceiveUpdatable(updatable);
				if (!ticker.IsRunning())
					ticker.Start();
			}
			if (ticker.Updatables.Count > 0)
			{
				while (data.AddOffset.TryDequeue(out TimeSpan offset))
					ticker.Offset(offset);
				ticker.PerformTick();
			}
			Thread.Sleep(1000);
		}
	}

	/// <summary>
	/// Delegate user input from the console to a separate thread to prevent blocking of the main thread.<br/>
	/// Cancelling from this thread is intended.
	/// </summary>
	/// <param name="data">Concurrent data to send to the ticker thread.</param>
	static void GetUserInput(ConcurrentData data)
	{
		StringComparison sOptions = StringComparison.OrdinalIgnoreCase;
		string pattern = @"(-?\d+)(\p{L}+)";
		RegexOptions rOptions = RegexOptions.IgnoreCase;
		Regex regex = new(pattern, rOptions);

		StringBuilder options = new();
		options.AppendLine("Options include:");
		options.AppendLine("quit: Stop all execution");
		options.AppendLine("add: Add an Updatable to the ticker");
		options.AppendLine("offset: Add an offset time to the ticker");
		Console.WriteLine(options);

		while (true)
		{
			string input = Console.ReadLine();
			if (input.Equals("quit", sOptions))
			{
				CTS.Cancel();
				Console.WriteLine("Quitting");
				break;
			}
			else if (input.Equals("add", sOptions))
			{
				Console.WriteLine("1 for Demo1\n2 for Demo2");
				string choice = Console.ReadLine();
				if (int.TryParse(choice, out int select))
				{
					if (select == 1)
						data.AddUpdatables.Enqueue(new TickerDemo1());
					else if (select == 2)
						data.AddUpdatables.Enqueue(new TickerDemo2());
					else
						Console.WriteLine($"{choice} is not an option.");
				}
			}
			else if (input.Equals("offset", sOptions))
			{
				StringBuilder instruction = new();
				instruction.AppendLine("Provide an offset time, negative values allowed, at least 1 duration unit");
				instruction.AppendLine("Allowed units: days(d), hours(h), minutes(min), seconds(s), milliseconds(mil), microseconds(mic)");
				Console.WriteLine(instruction);

				string time = Console.ReadLine();
				int d = 0, h = 0, min = 0, s = 0, mil = 0, mic = 0;
				Match match = regex.Match(time);
				while(match.Success)
				{
					Group duration = match.Groups[1];
					Group unit = match.Groups[2];
					if (unit.Value.StartsWith("d", sOptions))
						int.TryParse(duration.Value, out d);
					else if (unit.Value.StartsWith("h", sOptions))
						int.TryParse(duration.Value, out h);
					else if (unit.Value.StartsWith("min", sOptions))
						int.TryParse(duration.Value, out min);
					else if (unit.Value.StartsWith("s", sOptions))
						int.TryParse(duration.Value, out s);
					else if (unit.Value.StartsWith("mil", sOptions))
						int.TryParse(duration.Value, out mil);
					else if (unit.Value.StartsWith("mic", sOptions))
						int.TryParse(duration.Value, out mic);
					match = match.NextMatch();
				}

				TimeSpan offset = new(d, h, min, s, mil, mic);
				data.AddOffset.Enqueue(offset);
			}
		}
	}
}

/// <summary>
/// A collection of <see cref="ConcurrentQueue{T}"/>s to transfer data from the user input thread to the ticker thread.
/// </summary>
record ConcurrentData
{
	/// <summary>
	/// Sends new <see cref="Updatable"/>s to the ticker thread.
	/// </summary>
	public ConcurrentQueue<Updatable> AddUpdatables { get; init; } = [];

	/// <summary>
	/// Sends offset <see cref="TimeSpan"/>s to the ticker thread.
	/// </summary>
	public ConcurrentQueue<TimeSpan> AddOffset { get; init; } = [];
}

/// <summary>
/// Demo <see cref="Updatable"/> 1. These will always update first.
/// </summary>
class TickerDemo1 : Updatable
{
	protected override int Order => 1;

	public override void Update(double deltaTime)
	{
		Console.WriteLine($"{GetType()}: {deltaTime:N6}");
	}
}

/// <summary>
/// Demo <see cref="Updatable"/> 2. These will always update last.
/// </summary>
class TickerDemo2 : Updatable
{
	protected override int Order => 2;

	public override void Update(double deltaTime)
	{
		Console.WriteLine($"{GetType()}: {deltaTime:F6}");
	}
}
