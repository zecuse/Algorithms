#pragma once
#include <DeltaTime/Updatable.hpp>

namespace TickerDemo
{
class TickerDemo2 : public DeltaTime::Updatable
{
public:
	TickerDemo2(int ord = 2) : DeltaTime::Updatable(ord) {}
	void Update(double deltaTime) override;
};
}
