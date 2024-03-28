#pragma once
#include <chrono>
#include <queue>
#include <semaphore>

namespace Concurrent
{
template<class T>
class Queue
{
	std::queue<T> que = {};
	std::binary_semaphore sema { 1 };
public:
	bool push(const T &item, std::chrono::duration<double, std::milli> timeout)
	{
		if (sema.try_acquire_for(timeout))
		{
			que.push(item);
			sema.release();
			return true;
		}

		return false;
	}

	bool pop(T &item, std::chrono::duration<double, std::milli> timeout)
	{
		if (!que.empty() && sema.try_acquire_for(timeout))
		{
			item = que.front();
			que.pop();
			sema.release();
			return true;
		}

		return false;
	}
};
}