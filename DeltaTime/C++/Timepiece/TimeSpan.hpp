/***************************************
 *  @file    TimeSpan.hpp
 *  @brief   A data type representing a span of time from days to nanoseconds.
 **************************************/
#pragma once
#include <chrono>

namespace Timepiece
{
/** @addtogroup Units Units of duration
 *  @brief   Each available unit of time from days to nanoseconds.
 *  @details Unlike in the standard which defines each unit as an exact value,
 * each of these units are defined in reference to the next unit closest to
 * the base unit of seconds.
 * 
 * Type double is required to allow for fractional parts of the unit.
 * A fractional part in one unit will precisely equate to the whole part of
 * smaller units within the degree of double point precision.
 * That is, for 1.5 seconds, the 0.5 will exactly equal 500 milliseconds.
 *  @{
 */
typedef std::chrono::duration<double> secs;
typedef std::chrono::duration<double, std::ratio_multiply<std::ratio<60>, secs::period>> mins;
typedef std::chrono::duration<double, std::ratio_multiply<std::ratio<60>, mins::period>> hrs;
typedef std::chrono::duration<double, std::ratio_multiply<std::ratio<24>, hrs::period>> das;
typedef std::chrono::duration<double, std::ratio_multiply<secs::period, std::ratio<1000>>> ms;
typedef std::chrono::duration<double, std::ratio_multiply<ms::period, std::ratio<1000>>> us;
typedef std::chrono::duration<double, std::ratio_multiply<us::period, std::ratio<1000>>> ns;
/**@}*/

/***************************************
 *  @struct TimeSpan
 *  @brief   A data type representing a span of time from days to nanoseconds.
 *  @details This struct is inspired by the
 *  [TimeSpan](https://learn.microsoft.com/en-us/dotnet/api/system.timespan?view=net-8.0)
 *  struct found in the C# language.
 *  @see
 * * @ref Units 
 * * @ref Components
 **************************************/
struct TimeSpan
{
	/** @addtogroup Components TimeSpan composition
	 *  @brief   Each component comprising the duration of a TimeSpan.
	 *  @details Each component is a signed double representing the count of
	 * the @ref Units it represents. They are only constrained by the limits
	 * of the size of a signed double on the operating system.
	 * 
	 * -300.5 minutes is functionally equivalent to 5 hours and 30 seconds
	 * in the past from some chrono::timepoint.
	 *  @{
	 */
	das days{ 0 };
	hrs hours{ 0 };
	mins minutes{ 0 };
	secs seconds{ 0 };
	ms millis{ 0 };
	us micros{ 0 };
	ns nanos{ 0 };
	/**@}*/

	/**
	 *  @brief   Get the total duration of this TimeSpan.
	 *  @tparam  T One of the available units defined in the @ref Units group.
	 *  @return  The total amount of time represented by the unit T.
	 */
	template<typename T>
	inline T Count() const
	{ return days + hours + minutes + seconds + millis + micros + nanos; }
};
}
