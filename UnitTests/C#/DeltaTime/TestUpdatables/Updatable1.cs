using DeltaTime;

namespace UnitTests.DeltaTime.TestUpdatables;

/// <summary>
/// Test class to receive a deltaTime.
/// </summary>
internal class Updatable1 : Updatable
{
	protected override int Order => 1;

	public double Time { get; set; } = 0.0;

	public override void Update(double deltaTime) => Time = deltaTime;
}
