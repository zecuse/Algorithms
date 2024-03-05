#pragma once
#include <chrono>
#include <queue>
#include <semaphore>

namespace Concurrent
{
template<class T>
class Queue
{
	bool awake = false;
	std::queue<T> que = {};
	std::binary_semaphore sema = { 0 };
public:
	void Awake()
	{
		if (!awake)
			sema.release();
		awake = true;
	}

	void push(const T &item)
	{
		sema.acquire();
		que.push(item);
		sema.release();
	}

	bool pop(T &item, std::chrono::duration<double, std::chrono::milliseconds> timeout)
	{
		if (sema.try_acquire_for(timeout))
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