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
	virtual void Update(double) = 0;
	auto operator<=>(const Updatable &rhs) const
	{ return order <=> rhs.Order; }
	Updatable &operator=(Updatable &rhs)
	{
		order = rhs.Order;
		return *this;
	}
};
}
