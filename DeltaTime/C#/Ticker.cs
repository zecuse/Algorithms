using System.Diagnostics;

namespace DeltaTime;

/// <summary>
/// A class analogous to the OnUpdate loop often found in game engines.<br/>
/// This is meant to be driven from another loop.
/// </summary>
public class Ticker()
{
	/// <summary>
	/// All of the <see cref="Updatable"/> instances that will be updated each iteration.
	/// </summary>
	public List<Updatable> Updatables { get; set; } = [];

	/// <summary>
	/// A <see cref="Stopwatch"/> used to control the calculation of a deltaTime.<br/>
	/// This is based on the number of ticks as counted by the system<br/>
	/// and the frequency of the clock used by <see cref="Stopwatch"/>.
	/// </summary>
	Stopwatch Timer { get; } = new();

	/// <summary>
	/// The time at the end of the last <see cref="PerformTick"/> iteration.
	/// </summary>
	TimeSpan PrevTime { get; set; } = TimeSpan.Zero;

	/// <summary>
	/// Creates an offset from the current time to jump the <see cref="Updatables"/>.<br/>
	/// If an <see cref="Updatable"/> consistently runs exactly the same over an hour of time, an offset of<br/>
	/// 45 minutes at the beginning of this hour will instantaneously fast forward 45 minutes,<br/>
	/// provided this Updatable properly handles updating with such a large deltaTime.
	/// </summary>
	TimeSpan OffsetTime { get; set; } = TimeSpan.Zero;

	/// <summary>
	/// Determine if the <see cref="Stopwatch"/> is currently ticking.
	/// </summary>
	/// <returns><see langword="true"/> if the <see cref="Timer"/> is currently running, <see langword="false"/> otherwise.</returns>
	public bool IsRunning() => Timer.IsRunning;

	/// <summary>
	/// Start or resume the <see cref="Stopwatch"/>.
	/// </summary>
	public void Start() => Timer.Start();

	/// <summary>
	/// Stop the <see cref="Stopwatch"/>, reset its ticks to 0, and start it immediately.
	/// </summary>
	public void Restart() => Timer.Restart();

	/// <summary>
	/// Stop the <see cref="Stopwatch"/>.
	/// </summary>
	public void Pause() => Timer.Stop();

	/// <summary>
	/// Stop the <see cref="Stopwatch"/> and reset its ticks to 0.
	/// </summary>
	public void Reset() => Timer.Reset();

	/// <summary>
	/// Get the current elapsed time of the <see cref="Timer"/> as a <see cref="TimeSpan"/>.
	/// </summary>
	/// <returns>A <see cref="TimeSpan"/> representing the elapsed since the last <see cref="Start"/> or <see cref="Restart"/>.</returns>
	public TimeSpan GetTime() => Timer.Elapsed;

	/// <summary>
	/// Change the deltaTime for the next iteration of <see cref="PerformTick"/>.<br/>
	/// A positive <see cref="TimeSpan"/> moves time forward and negative backward.
	/// </summary>
	/// <param name="offset">A <see cref="TimeSpan"/> representing how much time should change.</param>
	public void Offset(TimeSpan offset) => OffsetTime = offset;

	/// <summary>
	/// Add an <see cref="Updatable"/> to begin receiving deltaTime updates.
	/// </summary>
	/// <param name="updatable">The <see cref="Updatable"/> to begin updating.</param>
	public void ReceiveUpdatable(Updatable updatable)
	{
		if (Updatables.Count == 0)
			Updatables.Add(updatable);
		else if (Updatables.Last().CompareTo(updatable) < 0)
			Updatables.Add(updatable);
		else if (Updatables.First().CompareTo(updatable) > 0)
			Updatables.Insert(0, updatable);
		else
		{
			int idx = Updatables.BinarySearch(updatable);
			if (idx < 0)
				idx = ~idx;
			Updatables.Insert(idx, updatable);
		}
	}

	/// <summary>
	/// Calculate a deltaTime and send it to all <see cref="Updatables"/>.<br/>
	/// <see cref="OffsetTime"/> will be reset to <see cref="TimeSpan.Zero"/>.<br/>
	/// <see cref="PrevTime"/> will receive the currently elapsed time AFTER all <see cref="Updatables"/> have been updated.
	/// </summary>
	public void PerformTick()
	{
		TimeSpan now = Timer.Elapsed;
		double deltaTime = now.TotalMilliseconds - PrevTime.TotalMilliseconds + OffsetTime.TotalMilliseconds;
		OffsetTime = TimeSpan.Zero;

		foreach (var updatable in Updatables)
			updatable.Update(deltaTime);
		PrevTime = Timer.Elapsed;
	}
}
