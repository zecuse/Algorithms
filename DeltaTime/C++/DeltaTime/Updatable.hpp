#pragma once
#include <compare>

namespace DeltaTime
{
class Updatable
{
	int order;
public:
	const int &Order = order;
	Updatable(int ord = 10) : order(ord) {}
	void Update(double);
	auto operator<=>(const Updatable &rhs) const
	{ return order <=> rhs.Order; }
};
}
