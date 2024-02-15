using DeltaTime;

namespace UnitTests.DeltaTime;

/// <summary>
/// A series of tests for controlling the <see cref="Ticker"/>.
/// </summary>
class TimerControlTests : BaseTickerTests
{
	/// <summary>
	/// Ensure that the <see cref="Ticker"/> has begun ticking.
	/// </summary>
	[Test]
	public void Start_Test() => Assert.That(ticker.IsRunning());

	/// <summary>
	/// Test that the <see cref="Ticker"/> has stopped, reset, and begun again.<br/>
	/// Millisecond precision is needed because the execution of lines of code is on the order of Microseconds.
	/// </summary>
	[Test]
	public void Restart_Test()
	{
		Thread.Sleep(200);
		ticker.Restart();

		Assert.Multiple(() =>
		{
			Assert.That(ticker.IsRunning());
			Assert.That(ticker.GetTime().Milliseconds, Is.Zero);
		});
	}

	/// <summary>
	/// Test that the <see cref="Ticker"/> has stopped, is no longer running, but not reset.
	/// </summary>
	[Test]
	public void Pause_Test()
	{
		Thread.Sleep(200);
		ticker.Pause();

		Assert.Multiple(() =>
		{
			Assert.That(!ticker.IsRunning());
			Assert.That(ticker.GetTime().Milliseconds, Is.GreaterThan(0));
		});
	}

	/// <summary>
	/// Test that the <see cref="Ticker"/> has stopped and been reset.
	/// </summary>
	[Test]
	public void Reset_Test()
	{
		Thread.Sleep(200);
		ticker.Reset();

		Assert.Multiple(() =>
		{
			Assert.That(!ticker.IsRunning());
			Assert.That(ticker.GetTime().Microseconds, Is.Zero);
		});
	}
}
