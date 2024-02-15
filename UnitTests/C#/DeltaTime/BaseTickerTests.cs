using DeltaTime;

namespace UnitTests.DeltaTime;

/// <summary>
/// Base test class for setting up and tearing down tests.
/// </summary>
[TestFixture]
class BaseTickerTests
{
	/// <summary>
	/// Reference to the <see cref="Ticker"/> class to be tested.
	/// </summary>
	protected Ticker ticker;

	/// <summary>
	/// Only create the <see cref="Ticker"/> once.
	/// </summary>
	[OneTimeSetUp]
	public void Init() => ticker = new();

	/// <summary>
	/// Begin the <see cref="Ticker"/>'s timer at the start of every test.
	/// </summary>
	[SetUp]
	public void SetUp() => ticker.Start();

	/// <summary>
	/// Reset the <see cref="Ticker"/>'s timer at the end of every test.
	/// </summary>
	[TearDown]
	public void TearDown() => ticker.Reset();
}