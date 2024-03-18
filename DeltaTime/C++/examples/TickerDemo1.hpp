#pragma once
#include <DeltaTime/Updatable.hpp>

namespace TickerDemo
{
class TickerDemo1 : public DeltaTime::Updatable
{
public:
	TickerDemo1(int ord = 1) : DeltaTime::Updatable(ord) {}
	void Update(double deltaTime) override;
};
}
