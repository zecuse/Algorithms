using DeltaTime;

namespace UnitTests.DeltaTime;

/// <summary>
/// A series of tests that need to be executed in order.
/// </summary>
class ContinuityTests : BaseTickerTests
{
	/// <summary>
	/// Test that the <see cref="Ticker"/> can receive an <see cref="Updatable"/>.
	/// </summary>
	/// <param name="updatable">The <see cref="Updatable"/> to be received.</param>
	/// <returns>A count of every received <see cref="Updatable"/>.</returns>
	[TestCaseSource(typeof(DataSources), nameof(DataSources.Cases)), Order(1)]
	public int ReceiveUpdatable_Tests(Updatable updatable)
	{
		ticker.ReceiveUpdatable(updatable);

		return ticker.Updatables.Count;
	}

	/// <summary>
	/// Runs after <see cref="ReceiveUpdatable_Tests(Updatable)"/><br/>
	/// and tests that all <see cref="Updatable"/>s are sorted by their <see cref="Updatable.Order"/>.
	/// </summary>
	[Test, Order(2)]
	public void UpdatablesSorted_Test() => Assert.That(ticker.Updatables, Is.Ordered);

	/// <summary>
	/// Ensure that the <see cref="Updatable"/>s received the same deltaTime.
	/// </summary>
	[Test, Order(2)]
	public void PerformTick_Test()
	{
		double[] times = new double[3];

		ticker.PerformTick();
		for (int i = 0; i < ticker.Updatables.Count; i++)
		{
			Updatable updatable = ticker.Updatables[i];
			if (updatable is TestUpdatables.Updatable1 up1)
				times[i] = up1.Time;
			else if (updatable is TestUpdatables.Updatable2 up2)
				times[i] = up2.Time;
			else if (updatable is TestUpdatables.Updatable3 up3)
				times[i] = up3.Time;
		}

		foreach (double t in times)
			Assert.That(t, Is.GreaterThan(0.0));
		Assert.Multiple(() =>
		{
			Assert.That(times[0], Is.EqualTo(times[1]));
			Assert.That(times[1], Is.EqualTo(times[2]));
		});
	}
}

/// <summary>
/// A source class containing test cases for the <see cref="ContinuityTests"/>.
/// </summary>
class DataSources
{
	/// <summary>
	/// An enumerable of <see cref="TestCaseData"/> for the <see cref="ContinuityTests.ReceiveUpdatable_Tests(Updatable)"/> test.
	/// </summary>
	public static IEnumerable<TestCaseData> Cases
	{
		get
		{
			yield return new TestCaseData(new TestUpdatables.Updatable3()).Returns(1);
			yield return new TestCaseData(new TestUpdatables.Updatable1()).Returns(2);
			yield return new TestCaseData(new TestUpdatables.Updatable2()).Returns(3);
		}
	}
}
