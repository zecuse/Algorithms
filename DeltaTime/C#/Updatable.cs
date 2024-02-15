namespace DeltaTime;

/// <summary>
/// An abstract class to identify anything that can be updated with a deltaTime.
/// </summary>
public abstract class Updatable : IComparable<Updatable>
{
	/// <summary>
	/// Determines when any Updatable should be updated before or after any other.
	/// </summary>
	protected virtual int Order { get; } = 10;

	/// <summary>
	/// Defines how an Updatable will respond to receiving a deltaTime.
	/// </summary>
	/// <param name="deltaTime">A, usually small and less than 1, value in total milliseconds between tick iterations.</param>
	public abstract void Update(double deltaTime);

	/// <summary>
	/// Sort all Updatables with respect to their <see cref="Order"/>.
	/// </summary>
	/// <param name="that">Another Updatable.</param>
	/// <returns>If one of the following is true:<br/>
	/// <code>
	/// 1. Negative: <see langword="this"/> updatable should precede <see href="that"/><br/>
	/// 2. Zero:     <see langword="this"/> updatable is logically equivalent to <see href="that"/>, order undefined<br/>
	/// 3. Positive: <see langword="this"/> updatable should procede <see href="that"/><br/>
	/// 4. Null:     <see langword="this"/> always precedes a null <see href="that"/>
	/// </code></returns>
	public int CompareTo(Updatable? that)
	{
		if (that == null)
			return -1;
		return this.Order.CompareTo(that.Order);
	}
}
